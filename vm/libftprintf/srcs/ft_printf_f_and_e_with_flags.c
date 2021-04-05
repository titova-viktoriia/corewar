/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_eE.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:20 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/23 15:48:32 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	part_2_without_minus(int len, t_data *data)
{
	if (data->flag_zero == 0)
	{
		if (data->fl_znak != 0)
		{
			print_in_while(' ', data->width - len - 1, data);
			ft_putchar_with_counter(data->fl_znak, data);
		}
		else
			print_in_while(' ', data->width - len, data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
	if (data->flag_zero == 1)
	{
		if (data->fl_znak != 0)
		{
			ft_putchar_with_counter(data->fl_znak, data);
			data->width = data->width - 1;
		}
		print_in_while('0', data->width - len, data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
}

void		ft_printf_fe_flags(long double nb, int len, t_data *data)
{
	if (nb < 0)
		data->fl_znak = '-';
	else if (data->flag_plus == 1 && nb >= 0)
		data->fl_znak = '+';
	else if (data->flag_space == 1)
		data->fl_znak = ' ';
	if (data->flag_minus == 0)
		part_2_without_minus(len, data);
	if (data->flag_minus == 1)
	{
		if (data->fl_znak != 0)
		{
			ft_putchar_with_counter(data->fl_znak, data);
			data->width = data->width - 1;
		}
		ft_putstr_with_counter(data->bufferdata, data);
		print_in_while(' ', data->width - len, data);
	}
}
