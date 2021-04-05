/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_in_while.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:52 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 17:25:44 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_in_while(char c, int count, t_data *data)
{
	if (c == 0)
		return ;
	if (count < 1)
		return ;
	data->len = data->len + count;
	while (count > 0)
	{
		write(1, &c, 1);
		count--;
	}
}
