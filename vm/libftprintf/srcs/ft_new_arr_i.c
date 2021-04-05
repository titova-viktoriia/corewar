/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pole_and_bufferdata.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:58 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 21:26:53 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		**ft_new_arr_i(int a, int b)
{
	int		**masi;
	int		i;

	masi = (int **)malloc(sizeof(int*) * (a));
	i = 0;
	while (i < a)
	{
		masi[i] = (int *)malloc(sizeof(int) * b);
		i++;
	}
	return (masi);
}
