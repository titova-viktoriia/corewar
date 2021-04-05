/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:33:49 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:15:30 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void		no_dispatcher(t_printf *p)
{
	if ((p->padding = p->width - 1) > 0)
	{
		padding_left(p);
		p->len += write(p->fd, p->fmt, 1);
		padding_right(p);
	}
	else
		p->len += write(p->fd, p->fmt, 1);
}

static void		set_dispatchers(void (*dispatchers[]) (t_printf*))
{
	int		i;

	i = 0;
	while (i < 127)
		dispatchers[i++] = no_dispatcher;
	dispatchers['d'] = ft_putnb_printf;
	dispatchers['D'] = ft_putnb_printf;
	dispatchers['i'] = ft_putnb_printf;
	dispatchers['b'] = ft_putnb_printf_2;
	dispatchers['o'] = ft_putnb_printf_8;
	dispatchers['O'] = ft_putnb_printf_8;
	dispatchers['u'] = ft_putnb_printf_10;
	dispatchers['U'] = ft_putnb_printf_10;
	dispatchers['x'] = ft_putnb_printf_16;
	dispatchers['X'] = ft_putnb_printf_16;
	dispatchers['f'] = ft_putdbl_printf;
	dispatchers['F'] = ft_putdbl_printf;
	dispatchers['c'] = ft_putchar_printf;
	dispatchers['C'] = ft_putchar_printf;
	dispatchers['s'] = ft_putstr_printf;
	dispatchers['S'] = ft_putstr_printf;
	dispatchers['p'] = ft_putptr_printf;
}

static void		read_format(t_printf *p)
{
	void	(*dispatchers[127]) (t_printf*);

	set_dispatchers(dispatchers);
	while (*p->fmt)
	{
		if (*p->fmt == '%')
		{
			if (!*++p->fmt)
				break ;
			else
			{
				parse_format(p);
				if (!*p->fmt)
					break ;
				dispatchers[(int)*p->fmt](p);
			}
		}
		else if (*p->fmt == '{')
			change_colour(p);
		else
			p->len += write(p->fd, p->fmt, 1);
		p->fmt++;
	}
}

int				ft_dprintf(int fd, const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = fd;
	p.fmt = (char *)format;
	va_start(p.ap, format);
	read_format(&p);
	va_end(p.ap);
	return (p.len);
}

int				ft_printf(const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.fmt = (char *)format;
	va_start(p.ap, format);
	read_format(&p);
	va_end(p.ap);
	return (p.len);
}
