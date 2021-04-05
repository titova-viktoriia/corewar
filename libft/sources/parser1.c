/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:49:20 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/11/12 11:50:08 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	padding_left(t_printf *p)
{
	char	c;

	if (p->padding)
	{
		c = p->f.is_zero ? '0' : ' ';
		if (!p->f.is_minus)
			while (p->padding--)
				p->len += write(p->fd, &c, 1);
	}
}

void	padding_right(t_printf *p)
{
	char	c;

	if (p->padding)
	{
		c = p->f.is_zero ? '0' : ' ';
		if (p->f.is_minus)
			while (p->padding--)
				p->len += write(p->fd, &c, 1);
	}
}
