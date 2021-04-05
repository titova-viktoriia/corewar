/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:46:38 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:47:27 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "dasm.h"

void		ft_throw(char *s)
{
	errno ? perror(s) : ft_putendl_fd(s, 2);
	exit(1);
}

int32_t		get_int(const uint8_t *code, size_t size)
{
	int32_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = code[0] & 0x80;
	i = 0;
	while (size--)
	{
		if (sign)
			result += (code[size] ^ 0xFF) << (i++ * 8);
		else
			result += code[size] << (i++ * 8);
	}
	if (sign)
		result = ~(result);
	return (result);
}
