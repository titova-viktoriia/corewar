/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:12:18 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/11/12 12:14:10 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			ft_wcharlen(unsigned wc)
{
	if (wc < 0x80)
		return (1);
	else if (wc < 0x800)
		return (2);
	else if (wc < 0x10000)
		return (3);
	return (4);
}

void			change_colour(t_printf *p)
{
	int len;

	p->printed = 5;
	if (!ft_strncmp(p->fmt, "{red}", (len = 4)))
		p->len += write(p->fd, "\033[31m", 5);
	else if (!ft_strncmp(p->fmt, "{green}", (len = 6)))
		p->len += write(p->fd, "\033[32m", 5);
	else if (!ft_strncmp(p->fmt, "{yellow}", (len = 7)))
		p->len += write(p->fd, "\033[33m", 5);
	else if (!ft_strncmp(p->fmt, "{blue}", (len = 5)))
		p->len += write(p->fd, "\033[34m", 5);
	else if (!ft_strncmp(p->fmt, "{purple}", (len = 7)))
		p->len += write(p->fd, "\033[35m", 5);
	else if (!ft_strncmp(p->fmt, "{cyan}", (len = 5)))
		p->len += write(p->fd, "\033[36m", 5);
	else if (!ft_strncmp(p->fmt, "{eoc}", (len = 4)))
		p->len += write(p->fd, "\033[37m", 5);
	else if (!(len = 0))
	{
		p->len += write(p->fd, p->fmt, 1);
		p->printed = 1;
	}
	p->fmt += len;
}
