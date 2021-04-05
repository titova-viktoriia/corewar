/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:11:15 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/11/12 12:11:50 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_printf(t_printf *p)
{
	void			*pointer;
	uintmax_t		tmp;

	pointer = va_arg(p->ap, void *);
	p->printed = 0;
	tmp = (uintmax_t)pointer;
	while (tmp && ++p->printed)
		tmp /= 16;
	p->f.is_sharp = 0;
	p->width -= (p->f.is_zero ? 2 : 0);
	p->padding = (p->printed > p->width - 3) ? 0 :
		p->width - 3 - p->printed;
	p->f.is_sharp = 1;
	p->f.is_pointer = 1;
	ft_itoa_base_printf((uintmax_t)pointer, 16, p);
}
