/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljacquet <ljacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:35:44 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_atoi_long_long(const char *str)
{
	long long		k;
	int				znak;

	k = 0;
	znak = 1;
	while (*str == '\n' || *str == '\v' || *str == '\t' ||
		*str == '\r' || *str == ' ' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			znak = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		k = k * 10 + (*str - '0');
		str++;
	}
	return (k * znak);
}
