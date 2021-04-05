/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itobufferdata_llu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:25 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/05 17:33:50 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	buffd_llu(unsigned long long b, t_data *d, long long l, int bs)
{
	if (b == 0)
		d->bufferdata[l - 1] = '0';
	while (l > 0 && b > 0)
	{
		d->bufferdata[l - 1] = b % bs + '0';
		b = b / bs;
		l--;
	}
}
