/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:33 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/23 19:09:35 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				count_of_second_part(t_data *data)
{
	int		count;

	count = 0;
	if (data->precision > 0)
		count = data->precision + 1;
	if (data->flag_hash == 1 && (data->precision == 0 || data->flag_dot == 1))
		count++;
	if (data->flag_dot == 0 && data->precision == -1)
	{
		data->precision = 6;
		count = 7;
	}
	if (data->flag_dot == 1 && data->precision == -1)
		data->precision = 0;
	return (count);
}
