/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pole_and_bufferdata.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:58 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 18:17:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_pole_and_bufferdata(long long len, t_data *data)
{
	get_parametr_pole(data, len);
	if (data->fl_ppole_int == 1)
		print_in_while(' ', data->fl_ppole_long, data);
	print_in_while(data->fl_znak, 1, data);
	print_in_while('0', data->fl_0pole_long, data);
	if (data->fl_0faktor == 0)
		ft_putstr_with_counter(data->bufferdata, data);
	if (data->fl_ppole_int == 2)
		print_in_while(' ', data->fl_ppole_long, data);
	free(data->bufferdata);
}
