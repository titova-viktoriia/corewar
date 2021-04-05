/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:33 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/05 17:33:50 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_b(t_data *data)
{
	unsigned long long		b;
	long long				len;

	data->flag_space = 0;
	if (data->flag_l == 1)
		b = (unsigned long)va_arg(data->args, unsigned long int);
	else if (data->flag_l == 2)
		b = va_arg(data->args, unsigned long long int);
	else if (data->flag_h == 1)
		b = (unsigned short)va_arg(data->args, unsigned int);
	else if (data->flag_h == 2)
		b = (unsigned char)va_arg(data->args, unsigned int);
	else
		b = va_arg(data->args, unsigned int);
	len = ft_count_of_digits_llu(b, 2);
	if (!(data->bufferdata = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	data->bufferdata[len] = '\0';
	buffd_llu(b, data, len, 2);
	data->fl_znak = 0;
	print_pole_and_bufferdata(len, data);
}
