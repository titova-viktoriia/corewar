/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:13:13 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/05 17:33:50 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_printf_min_lld(t_data *data)
{
	unsigned long long int	b1;
	long long				len;

	b1 = 9223372036854775807;
	len = 19;
	if (!(data->bufferdata = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	data->bufferdata[len] = '\0';
	buffd_llu(b1 + 1, data, len, 10);
	data->fl_znak = '-';
	print_pole_and_bufferdata(len, data);
}

static void			ft_printf_else(long long b, t_data *data)
{
	long long			len;

	len = ft_count_of_digits(b);
	if (!(data->bufferdata = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	data->bufferdata[len] = '\0';
	itobufferdata(b, data, len);
	print_pole_and_bufferdata(len, data);
}

void				ft_printf_d(t_data *data)
{
	long long int		b;

	if (data->flag_hash == 1)
		data->flag_hash = 0;
	if (data->flag_l == 1)
		b = (long long)(long)va_arg(data->args, long int);
	else if (data->flag_l == 2)
		b = (long long)va_arg(data->args, long long int);
	else if (data->flag_h == 1)
		b = (long long)(short)va_arg(data->args, int);
	else if (data->flag_h == 2)
		b = (long long)(signed char)va_arg(data->args, int);
	else
		b = (long long)va_arg(data->args, int);
	if ((b + 1) == -9223372036854775807)
		ft_printf_min_lld(data);
	else
		ft_printf_else(b, data);
}
