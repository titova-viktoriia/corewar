/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldtobi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:44:26 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/19 11:46:36 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*bitostr(unsigned long a, int len, char filler, char *str)
{
	int		i;

	if (str)
	{
		i = len;
		ft_memset(str, filler, len);
		str[i] = 0;
		if (!a)
			str[i - 1] = '0';
		while (a && --i > -1)
		{
			str[i] = a % 10 + '0';
			a /= 10;
		}
		str[len] = 0;
	}
	return (str + len);
}

t_bi	pow_of_two(unsigned long pow)
{
	t_bi	bi;
	int		i;

	ft_bzero(&bi, sizeof(bi));
	bi.num[0] = 1;
	while (pow--)
	{
		i = LINT_SIZE;
		while (--i > -1)
		{
			bi.num[i] <<= 1;
			if (bi.num[i] >= LINT_OVER)
			{
				bi.num[i] -= LINT_OVER;
				++bi.num[i + 1];
			}
		}
	}
	bi.num[LINT_SIZE] = 0;
	return (bi);
}

t_bi	bi_add(t_bi a, t_bi b)
{
	t_bi	res;
	int		i;

	ft_bzero(&res, sizeof(res));
	i = -1;
	while (++i < LINT_SIZE)
	{
		res.num[i] += a.num[i] + b.num[i];
		if (res.num[i] >= LINT_OVER)
		{
			res.num[i] -= LINT_OVER;
			res.num[i + 1] = 1;
		}
	}
	res.num[LINT_SIZE] = 0;
	return (res);
}

t_bi	ldtobi_2(unsigned long mnt, int exp)
{
	t_bi	bi;

	ft_bzero(&bi, sizeof(bi));
	while (exp > -1)
	{
		if (0x8000000000000000 & mnt)
			bi = bi_add(bi, pow_of_two(exp));
		mnt <<= 1;
		--exp;
	}
	return (bi);
}

t_bi	ldtobi(long double ld)
{
	t_bi	bi;
	t_ld	u_ld;

	u_ld.ld = ld;
	if (u_ld.s_ld.e >= LD_EXP_SHIFT)
		bi = ldtobi_2(u_ld.s_ld.m, u_ld.s_ld.e - LD_EXP_SHIFT);
	else
		ft_bzero(&bi, sizeof(bi));
	return (bi);
}
