/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:47 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 21:32:53 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_common_2(t_data *data)
{
	if (data->type == 'd' || data->type == 'i')
		ft_printf_d(data);
	if (data->type == 'u')
		ft_printf_u(data);
	if (data->type == 'o')
		ft_printf_o(data);
	if (data->type == 'b')
		ft_printf_b(data);
	if (data->type == 'I')
		ft_printf_mas_i(data);
	if (data->type == 'C')
		ft_printf_mas_c(data);
}

void			print_common(t_data *data)
{
	if (data->type == '%')
		ft_printf_percent(data);
	else if (data->type == 'c')
		ft_printf_c(data);
	else if (data->type == 's')
		ft_printf_s(data);
	else if (data->type == 'x' || data->type == 'X')
		ft_printf_xx(data);
	else if (data->type == 'p')
		ft_printf_p(data);
	else if (data->type == 'f')
		ft_printf_f(data);
	else if (data->type == 'e' || data->type == 'E')
		ft_printf_e(data);
	else
		print_common_2(data);
}
