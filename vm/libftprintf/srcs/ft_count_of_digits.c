/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_of_digits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:11:50 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/03 16:27:52 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		ft_count_of_digits(long long n)
{
	long long			count;

	count = 1;
	if (n < 0)
		n = n * (-1);
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
