/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			install_data(t_data *data)
{
	data->width = 0;
	data->precision = -1;
	data->flag_hash = 0;
	data->flag_minus = 0;
	data->flag_plus = 0;
	data->flag_space = 0;
	data->fl_ppole_long = 0;
	data->fl_ppole_int = 1;
	data->fl_0pole_long = 0;
	data->fl_znak_int = 0;
	data->fl_znak = 0;
	data->fl_0faktor = 0;
	data->flag_zero = 0;
	data->flag_h = 0;
	data->flag_l = 0;
	data->flag_large_l = 0;
	data->type = '0';
	data->flag_dot = 0;
	data->bufferdata = NULL;
}

int				ft_printf(const char *format, ...)
{
	int				len;
	t_data			*data;

	if (!(data = malloc(sizeof(t_data))))
		return (0);
	data->index = 0;
	data->len = 0;
	install_data(data);
	va_start(data->args, format);
	parse_and_print(data, format);
	va_end(data->args);
	len = data->len;
	free(data);
	return (len);
}
