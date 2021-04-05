/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:33 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/22 17:13:46 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_c_with_flags(t_data *data, char c)
{
	if (data->flag_minus == 1 && data->flag_zero == 1)
	{
		ft_putchar_with_counter(c, data);
		print_in_while('0', data->width - 1, data);
	}
	if (data->flag_minus == 1 && data->flag_zero == 0)
	{
		ft_putchar_with_counter(c, data);
		print_in_while(' ', data->width - 1, data);
	}
	if (data->flag_minus == 0 && data->flag_zero == 1)
	{
		print_in_while('0', data->width - 1, data);
		ft_putchar_with_counter(c, data);
	}
	if (data->flag_minus == 0 && data->flag_zero == 0)
	{
		print_in_while(' ', data->width - 1, data);
		ft_putchar_with_counter(c, data);
	}
}

void		ft_printf_c(t_data *data)
{
	char c;

	c = (char)va_arg(data->args, int);
	if (data->width > 1)
		ft_printf_c_with_flags(data, c);
	else
		ft_putchar_with_counter(c, data);
}
