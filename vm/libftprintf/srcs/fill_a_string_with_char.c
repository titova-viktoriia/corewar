/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_of_digits_llu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:01 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/22 17:12:01 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_a_string_with_char(char c, char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
}
