/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_of_digits_llu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:01 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/03 16:26:31 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		ft_count_of_digits_llu(unsigned long long n, int base)
{
	long long					count;
	unsigned long long			base1;

	base1 = (unsigned long long)base;
	count = 1;
	while (n > (base1 - 1))
	{
		n = n / base1;
		count++;
	}
	return (count);
}
