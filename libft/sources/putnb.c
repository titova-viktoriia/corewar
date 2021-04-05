/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:54:32 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/11/12 12:06:02 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnb_printf(t_printf *p)
{
	ft_putnb_printf_no_base(p);
}

void	ft_putnb_printf_2(t_printf *p)
{
	ft_putnb_printf_base(p, 2);
}

void	ft_putnb_printf_8(t_printf *p)
{
	ft_putnb_printf_base(p, 8);
}

void	ft_putnb_printf_10(t_printf *p)
{
	ft_putnb_printf_base(p, 10);
}

void	ft_putnb_printf_16(t_printf *p)
{
	ft_putnb_printf_base(p, 16);
}
