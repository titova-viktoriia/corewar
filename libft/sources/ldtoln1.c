/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldtoln1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:40:14 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/25 11:42:55 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ln_cmp(t_ln n1, t_ln n2)
{
	int		i;

	if (n1.exp > n2.exp)
		return (1);
	else if (n2.exp > n1.exp)
		return (-1);
	i = LN_SIZE;
	while (i--)
	{
		if (n1.mnt[i] > n2.mnt[i])
			return (1);
		if (n2.mnt[i] > n1.mnt[i])
			return (-1);
	}
	return (0);
}

t_ln			ln_lowshift(t_ln num, unsigned int shift)
{
	unsigned long		tmp[LN_SIZE * 2];
	unsigned int		bytes;
	unsigned int		bits;
	int					i;

	num.exp += shift;
	shift %= LN_SIZE * 8 * 8;
	ft_bzero(tmp, sizeof(tmp));
	bytes = shift / 64;
	bits = shift % 64;
	ft_memcpy(&(tmp[LN_SIZE - bytes]), num.mnt, LN_SIZE * 8);
	ft_memcpy(num.mnt, &(tmp[LN_SIZE]), LN_SIZE * 8);
	i = 0;
	while (i < LN_SIZE)
	{
		tmp[i + LN_SIZE - 1] = num.mnt[i] << (64 - bits);
		num.mnt[i] >>= bits;
		i++;
	}
	tmp[LN_SIZE * 2 - 1] = 0;
	while (--i && shift)
		num.mnt[i] |= tmp[i + LN_SIZE];
	return (num);
}

t_ln			ln_highshift(t_ln num, unsigned int shift)
{
	unsigned long		tmp[LN_SIZE * 2];
	unsigned int		bytes;
	unsigned int		bits;
	int					i;

	num.exp -= shift;
	shift %= LN_SIZE * 8 * 8;
	ft_bzero(tmp, sizeof(tmp));
	bytes = shift / 64;
	bits = shift % 64;
	ft_memcpy(&(tmp[bytes]), num.mnt, LN_SIZE * 8);
	ft_memcpy(num.mnt, &(tmp[0]), LN_SIZE * 8);
	i = 0;
	while (i < LN_SIZE)
	{
		tmp[i + LN_SIZE + 1] = num.mnt[i] >> (64 - bits);
		num.mnt[i] <<= bits;
		i++;
	}
	tmp[LN_SIZE] = 0;
	while (--i && shift)
		num.mnt[i] |= tmp[i + LN_SIZE];
	return (num);
}
