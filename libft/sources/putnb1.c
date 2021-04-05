/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnb1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:55:51 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/25 11:38:56 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

void			ft_itoa_base_set(uintmax_t n, int b, char *s, t_printf *p)
{
	int		len;
	char	c;

	len = p->printed;
	c = (*p->fmt == 'X') ? 'a' - 42 : 'a' - 10;
	while (len--)
	{
		s[len] = n % b + ((n % b < 10) ? '0' : c);
		n /= b;
	}
}

static void		ft_itoa_printf(intmax_t n, t_printf *p)
{
	char		s[99];
	uintmax_t	tmp;

	if (p->f.is_precision && !p->f.is_wildcard)
		p->f.is_zero = 0;
	if (!n && !p->f.is_precision)
		p->printed = 1;
	if (p->f.is_zero)
		p->precision = p->width;
	if ((n < 0 || p->f.is_plus || p->f.is_space) && p->f.is_zero)
		p->precision--;
	p->printed = p->printed > p->precision ? p->printed : p->precision;
	if (n < 0 || p->f.is_plus || p->f.is_space)
		p->printed++;
	p->padding = (p->printed > p->width) ? 0 : p->width - p->printed;
	padding_left(p);
	tmp = n < 0 ? -n : n;
	ft_itoa_base_set(tmp, 10, s, p);
	(p->f.is_space) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f.is_plus && n >= 0) ? s[0] = '+' : 0;
	p->len += write(p->fd, &s, p->printed);
	padding_right(p);
}

void			ft_itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	char		s[99];
	int			is_0;

	if (p->f.is_precision && !p->f.is_wildcard)
		p->f.is_zero = 0;
	if (!n && !p->f.is_precision)
		p->printed = 1;
	(p->f.is_sharp && b == 16 && (n || p->f.is_pointer)) ? p->width -= 2 : 0;
	(p->f.is_zero) ? p->precision = p->width : 0;
	is_0 = (p->printed < p->precision || !n) ? 1 : 0;
	p->printed = p->precision > p->printed ? p->precision : p->printed;
	(p->f.is_sharp && b == 8 && !is_0 && n) ?
		++p->printed : 0;
	if ((p->padding = (p->width - p->printed)) < 0)
		p->padding = 0;
	padding_left(p);
	if (p->f.is_sharp && b == 8 && !n &&
			(p->f.is_precision && p->precision == 0))
		p->len += write(p->fd, "0", 1);
	if (p->f.is_sharp && b == 16 && (n || p->f.is_pointer))
		p->len += write(p->fd, p->f.is_upcase ? "0X" : "0x", 2);
	ft_itoa_base_set(n, b, s, p);
	p->len += write(p->fd, &s, p->printed);
	padding_right(p);
}

void			ft_putnb_printf_no_base(t_printf *p)
{
	intmax_t	n;
	uintmax_t	tmp;

	if (p->f.is_j)
		n = va_arg(p->ap, intmax_t);
	else if (p->f.is_z)
		n = (intmax_t)va_arg(p->ap, ssize_t);
	else if (p->f.is_l || *p->fmt == 'D')
		n = (intmax_t)va_arg(p->ap, long);
	else if (p->f.is_ll)
		n = (intmax_t)va_arg(p->ap, long long);
	else if (p->f.is_h)
		n = (intmax_t)((short)va_arg(p->ap, int));
	else if (p->f.is_hh)
		n = (intmax_t)((char)va_arg(p->ap, int));
	else if (p->f.is_upcase_l)
		n = (intmax_t)va_arg(p->ap, int64_t);
	else
		n = ((intmax_t)va_arg(p->ap, int));
	p->printed = 0;
	tmp = n < 0 ? -n : n;
	while (tmp && ++p->printed)
		tmp /= 10;
	ft_itoa_printf(n, p);
}

void			ft_putnb_printf_base(t_printf *p, int base)
{
	uintmax_t	n;
	uintmax_t	tmp;

	if (p->f.is_j)
		n = va_arg(p->ap, uintmax_t);
	else if (p->f.is_z)
		n = (uintmax_t)va_arg(p->ap, size_t);
	else if (p->f.is_ll)
		n = (uintmax_t)va_arg(p->ap, unsigned long long);
	else if (p->f.is_l || *p->fmt == 'U' || *p->fmt == 'O')
		n = (uintmax_t)va_arg(p->ap, unsigned long);
	else if (p->f.is_h)
		n = (uintmax_t)((unsigned short)va_arg(p->ap, int));
	else if (p->f.is_hh)
		n = (uintmax_t)((unsigned char)va_arg(p->ap, int));
	else if (p->f.is_upcase_l)
		n = (uintmax_t)va_arg(p->ap, uint64_t);
	else
		n = (uintmax_t)va_arg(p->ap, unsigned int);
	p->printed = 0;
	tmp = n;
	while (tmp && ++p->printed)
		tmp /= base;
	ft_itoa_base_printf(n, base, p);
}
