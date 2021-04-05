/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:14:17 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 16:32:40 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_p(t_data *data)
{
	unsigned long int	add;
	size_t				len;

	add = (unsigned long)va_arg(data->args, unsigned long int);
	data->flag_hash = 1;
	get_str_xx(add, data);
	if (data->bufferdata == NULL)
		len = 2;
	else
		len = ft_strlen(data->bufferdata);
	data->type = 'x';
	if (data->width > len + 2)
		ft_printf_xx_with_flags(data, len);
	else
	{
		ft_putstr_with_counter("0x", data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
	free(data->bufferdata);
}
