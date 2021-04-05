/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:33 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/05 18:44:53 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_f(t_data *data)
{
	long double			b;
	size_t				len;

	if (data->flag_large_l == 0)
		b = (double)va_arg(data->args, double);
	if (data->flag_large_l == 1)
		b = (long double)va_arg(data->args, long double);
	get_float_str(b, data);
	len = ft_strlen(data->bufferdata);
	if (data->width > len)
		ft_printf_fe_flags((long double)b, len, data);
	else
	{
		if (b < 0)
			ft_putchar_with_counter('-', data);
		else if (b > 0 && data->flag_plus == 0 && data->flag_space == 1)
			ft_putchar_with_counter(' ', data);
		else if (b >= 0 && data->flag_plus == 1)
			ft_putchar_with_counter('+', data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
	free(data->bufferdata);
}
