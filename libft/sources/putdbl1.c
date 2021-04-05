/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putdbl1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:35:11 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/19 12:42:46 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			over1(unsigned long i, t_printf *p, char *str, unsigned long a)
{
	unsigned long		j;
	int					over;

	over = 0;
	if (str && str[(j = --i)] >= '5')
	{
		while (i > 0 && str[--i] == '9')
		{
			str[i] = '0';
			if (i == 0)
				over = 1;
		}
		if (j == i + 1 && str[j] == '5' && !a)
		{
			if (str[i] % 2)
				++str[i];
		}
		else if (!over)
			++str[i];
		else
			p->f.is_over = 1;
	}
	str ? str[j] = 0 : 0;
}

void			over(long double n, t_printf *p)
{
	if (n < 0)
		n = -n;
	if (((long double)(n - (size_t)n) >= 0.5L && (size_t)n % 2) ||\
			(!((size_t)n % 2) && (long double)(n - (size_t)n) > 0.5L))
		p->f.is_over = 1;
}

void			ft_printf_ld(t_printf *p, char *s, char *n, char *d)
{
	p->padding = (p->printed > p->width) ? 0 : p->width - p->printed;
	if (p->f.is_zero)
	{
		p->len += write(p->fd, s, ft_strlen(s));
		padding_left(p);
	}
	else
	{
		padding_left(p);
		p->len += write(p->fd, s, ft_strlen(s));
	}
	p->len += write(p->fd, n, ft_strlen(n));
	if (p->precision > 0 || p->f.is_sharp)
		p->len += write(p->fd, ".", 1);
	p->len += write(p->fd, d, ft_strlen(d));
	padding_right(p);
	free(s);
	free(n);
	free(d);
}
