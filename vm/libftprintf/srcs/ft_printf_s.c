/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:14:34 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/22 17:14:49 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_s_with_flags(int len, t_data *data)
{
	if (data->flag_minus == 1)
	{
		ft_putstr_with_counter(data->bufferdata, data);
		print_in_while(' ', data->width - len, data);
	}
	else if (data->flag_zero == 1)
	{
		print_in_while('0', data->width - len, data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
	else
	{
		print_in_while(' ', data->width - len, data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
}

void			ft_printf_s(t_data *data)
{
	int		len;

	data->bufferdata = (char *)va_arg(data->args, char *);
	if (data->bufferdata == NULL)
		data->bufferdata = "(null)";
	len = ft_strlen(data->bufferdata);
	if (data->precision > -1 && data->precision < len)
		len = data->precision;
	if (data->flag_dot == 1 && data->precision < 0)
		len = 0;
	if (data->width > (size_t)len)
		ft_printf_s_with_flags(len, data);
	else
		ft_putstr_with_counter(data->bufferdata, data);
}
