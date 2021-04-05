/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_from_10_to_16.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:09 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/22 18:29:04 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				count_of_digits_16(unsigned long int n)
{
	int			count;

	count = 1;
	while (n > 15)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

char			*ft_itoa_from_10_to_16(unsigned long int n, t_data *data)
{
	char			*arr;
	int				len;
	unsigned long	nb;
	char			*str;

	nb = n;
	if (data->type == 'p' || data->type == 'x')
		str = "0123456789abcdef";
	if (data->type == 'X')
		str = "0123456789ABCDEF";
	len = count_of_digits_16(nb);
	if (!(arr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	arr[len] = '\0';
	if (n == 0)
		arr[len - 1] = '0';
	while (len > 0 && nb > 0)
	{
		arr[len - 1] = str[nb % 16];
		nb = nb / 16;
		len--;
	}
	return (arr);
}
