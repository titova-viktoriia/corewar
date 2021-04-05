/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putdbl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:01:36 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/25 11:40:19 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_printf_inf_nan(t_printf *p)
{
	p->precision = 0;
	p->f.is_zero = 0;
	p->f.is_sharp = 0;
	if (p->f.is_nan)
		p->f.is_plus = 0;
	p->printed = 3;
	p->padding = (p->printed > p->width) ? 0 : p->width - p->printed;
	padding_left(p);
	if (p->f.is_inf && *p->fmt <= 'Z')
		p->len += write(p->fd, "INF", p->printed);
	if (p->f.is_inf && *p->fmt >= 'a')
		p->len += write(p->fd, "inf", p->printed);
	if (p->f.is_nan && *p->fmt <= 'Z')
		p->len += write(p->fd, "NAN", p->printed);
	if (p->f.is_nan && *p->fmt >= 'a')
		p->len += write(p->fd, "nan", p->printed);
	padding_right(p);
}

static void			ft_putdbl_printf_2(t_ln ln, t_printf *p, char *str)
{
	unsigned long		ul;
	unsigned long		i;
	int					pr;

	i = 0;
	pr = p->precision;
	if (ln.exp > 63 + (unsigned int)LN_EXP_SHIFT)
		ln = ldtoln(0.0);
	while (pr-- >= 0 && str)
	{
		ul = lntoul(ln);
		if (ul == 0)
			ln = ln_mul(ln, 10);
		else
			ln = ln_mul(ln_sub(ln, ldtoln((long double)ul)), 10);
		str[i] = lntoul(ln) + '0';
		str[i] = (str[i] == '/' || str[i] == ':') ? '0' : str[i];
		i++;
	}
	ln = ln_sub(ln, ldtoln((long double)lntoul(ln)));
	over1(i, p, str, ln.mnt[LN_SIZE - 1]);
}

static void			ft_putdbl_printf_3(t_bi bint, t_printf *p, char *str)
{
	int				len;
	char			*str2;
	int				i;
	uintmax_t		tmp;

	i = LINT_SIZE;
	len = (p->precision > 0 || p->f.is_sharp) ? 1 : 0;
	if (p->f.is_over)
		bint = bi_add(bint, ldtobi_2(0x8000000000000000, 0));
	while (bint.num[i] == 0 && i > 0)
		--i;
	tmp = bint.num[i];
	p->printed = (!tmp) ? 1 : 0;
	while (tmp && ++p->printed)
		tmp /= 10;
	str2 = ft_strnew(p->printed + 1);
	ft_itoa_base_set(bint.num[i--], 10, str2, p);
	ft_memcpy(str, str2, p->printed);
	free(str2);
	if (i > -1)
		str2 = str + p->printed;
	while (i > -1)
		str2 = bitostr(bint.num[i--], 18, '0', str2);
	len += ft_strlen(str);
	p->printed = p->precision + len;
}

static void			ft_putdbl_printf_1(long double n, t_printf *p)
{
	char			*str[3];

	(!p->f.is_precision) ? p->precision = 6 : 0;
	str[0] = ft_strnew(p->precision + 2);
	ft_putdbl_printf_2(ldtoln(n), p, str[0]);
	if (!p->precision && p->f.is_decimal)
		over(n, p);
	str[1] = ft_strnew(5000);
	ft_putdbl_printf_3(ldtobi(n), p, str[1]);
	str[2] = ft_strnew(1);
	if (n < 0 || p->f.is_plus || p->f.is_space)
	{
		p->printed++;
		(p->f.is_precision && p->f.is_zero) ? str[2][0] = ' ' : 0;
		(p->f.is_space) ? str[2][0] = ' ' : 0;
		(n < 0) ? str[2][0] = '-' : 0;
		(p->f.is_plus && n >= 0) ? str[2][0] = '+' : 0;
		ft_printf_ld(p, str[2], str[1], str[0]);
	}
	else
	{
		ft_printf_ld(p, str[2], str[1], str[0]);
	}
}

void				ft_putdbl_printf(t_printf *p)
{
	long double		ld;
	t_ld			u_ld;

	if (p->f.is_upcase_l)
		ld = va_arg(p->ap, long double);
	else
		ld = (long double)va_arg(p->ap, double);
	u_ld.ld = ld;
	if (u_ld.s_ld.e == 0x7FFF)
	{
		if (!(u_ld.s_ld.m << 1))
			p->f.is_inf = 1;
		else
			p->f.is_nan = 1;
		ft_printf_inf_nan(p);
	}
	else
	{
		if (u_ld.s_ld.e - LD_EXP_SHIFT < 64)
			p->f.is_decimal = 1;
		ft_putdbl_printf_1(ld, p);
	}
}
