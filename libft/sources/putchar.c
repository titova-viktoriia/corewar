/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:53:37 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/25 11:40:41 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

void		ft_putwchar(t_printf *p, unsigned wc, int len, int bytes)
{
	char	tmp[4];

	if (bytes <= len && bytes <= MB_CUR_MAX)
	{
		if (bytes == 1)
			tmp[0] = wc;
		else
		{
			if (bytes == 2)
				tmp[0] = ((wc & (0x1f << 6)) >> 6) | 0xC0;
			else
			{
				if (bytes == 3)
					tmp[0] = ((wc >> 12) & 0xf) | 0xE0;
				else
				{
					tmp[0] = ((wc >> 18) & 7) | 0xF0;
					tmp[1] = ((wc >> 12) & 0x3f) | 0x80;
				}
				tmp[bytes - 2] = ((wc >> 6) & 0x3f) | 0x80;
			}
			tmp[bytes - 1] = (wc & 0x3f) | 0x80;
		}
		p->len += write(p->fd, tmp, bytes);
	}
}

void		ft_putchar_printf(t_printf *p)
{
	unsigned	c;
	wchar_t		w;

	if (p->f.is_l || p->f.is_ll || p->f.is_upcase)
	{
		w = va_arg(p->ap, wchar_t);
		p->printed = ft_wcharlen(w);
		if ((p->padding = p->width - p->printed) < 0)
			p->padding = 0;
		padding_left(p);
		ft_putwchar(p, w, p->printed, p->printed);
		padding_right(p);
	}
	else
	{
		c = va_arg(p->ap, unsigned);
		if ((p->padding = p->width - 1) < 0)
			p->padding = 0;
		padding_left(p);
		p->len += write(p->fd, &c, 1);
		padding_right(p);
	}
}
