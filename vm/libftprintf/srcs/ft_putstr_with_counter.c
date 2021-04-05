/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_with_counter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:14:57 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/22 17:14:57 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_with_counter(char *str, t_data *data)
{
	size_t		len;
	size_t		i;

	i = 0;
	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (data->type == 's' && data->precision > -1 && data->precision < (int)len)
		len = data->precision;
	if (data->type == 's' && data->flag_dot == 1 && data->precision < 0)
		len = 0;
	data->len = data->len + len;
	while (i < len && str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}
