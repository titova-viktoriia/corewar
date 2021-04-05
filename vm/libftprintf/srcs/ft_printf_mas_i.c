/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:13:13 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 21:44:03 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_printf_mas_i_2(t_data *data, int **mas)
{
	size_t		a;
	int			b;
	long long	len;

	a = 0;
	while (a < data->width)
	{
		b = 0;
		while (b < data->precision)
		{
			len = ft_count_of_digits(mas[a][b]);
			if (!(data->bufferdata = (char *)malloc(sizeof(char) * (len + 1))))
				return ;
			data->bufferdata[len] = '\0';
			itobufferdata(mas[a][b], data, len);
			if (b != 0 && data->flag_space == 1)
				print_in_while(' ', 1, data);
			ft_putstr_with_counter(data->bufferdata, data);
			b++;
		}
		a++;
		if (a < data->width)
			print_in_while('\n', 1, data);
	}
}

void				ft_printf_mas_i(t_data *data)
{
	int			**mas;

	mas = va_arg(data->args, int **);
	ft_printf_mas_i_2(data, mas);
	free(data->bufferdata);
}
