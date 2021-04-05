/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pole_and_bufferdata.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:58 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 18:24:57 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf_mas_c(t_data *data)
{
	char			**mas;
	size_t			a;
	int				b;

	a = 0;
	mas = va_arg(data->args, char **);
	while (a < data->width)
	{
		b = 0;
		while (b < data->precision)
		{
			if (b != 0 && data->flag_space == 1)
				print_in_while(' ', 1, data);
			print_in_while(mas[a][b], 1, data);
			b++;
		}
		a++;
		if (a < data->width)
			print_in_while('\n', 1, data);
	}
}
