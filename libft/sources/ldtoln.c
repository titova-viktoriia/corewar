/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldtoln.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:41:39 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/19 11:42:35 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ln			ln_sum(t_ln n1, t_ln n2)
{
	int			i;
	t_ln		sum;

	ft_bzero(&sum, sizeof(sum));
	if (n1.exp > n2.exp)
		n2 = ln_lowshift(n2, n1.exp - n2.exp);
	else if (n2.exp > n1.exp)
		n1 = ln_lowshift(n1, n2.exp - n1.exp);
	i = -1;
	sum.exp = n1.exp;
	while (++i < LN_SIZE - 1)
	{
		sum.mnt[i] += n1.mnt[i] + n2.mnt[i];
		if ((sum.mnt[i] < n1.mnt[i]) || (sum.mnt[i] < n2.mnt[i]))
			++sum.mnt[i + 1];
	}
	sum.mnt[i] += n1.mnt[i] + n2.mnt[i];
	if ((sum.mnt[i] < n1.mnt[i]) || (sum.mnt[i] < n2.mnt[i]))
	{
		sum = ln_lowshift(sum, 1);
		sum.mnt[i] += 0x8000000000000000;
	}
	return (sum);
}

t_ln			ln_mul(t_ln n, unsigned long i)
{
	t_ln	sum;

	ft_bzero(&sum, sizeof(sum));
	while (i--)
		sum = ln_sum(sum, n);
	return (sum);
}

t_ln			ln_sub(t_ln n1, t_ln n2)
{
	int			i;
	t_ln		sub;

	if (((i = ln_cmp(n1, n2)) < 0))
		n1 = ln_lowshift(n1, n2.exp - n1.exp);
	else if (i > 0)
		n2 = ln_lowshift(n2, n1.exp - n2.exp);
	else
		return (ldtoln(0.0));
	ft_bzero(&sub, sizeof(sub));
	sub.exp = n1.exp;
	if (i < 0)
		sub.exp = n2.exp;
	i = 0;
	while (i < LN_SIZE - 1)
	{
		sub.mnt[i] += n1.mnt[i] - n2.mnt[i];
		if (sub.mnt[i] > n1.mnt[i])
			--sub.mnt[i + i];
		++i;
	}
	sub.mnt[i] += n1.mnt[i] - n2.mnt[i];
	while (!(sub.mnt[LN_SIZE - 1] & 0x8000000000000000) && (i-- > -1))
		sub = ln_highshift(sub, 1);
	return (sub);
}

unsigned long	lntoul(t_ln ln)
{
	unsigned long	ul;
	unsigned int	shift;

	shift = 64 - (ln.exp - LN_EXP_SHIFT + 1);
	ul = ln.mnt[LN_SIZE - 1];
	if (ln.exp > 63 + (unsigned int)LN_EXP_SHIFT)
		return ((unsigned long)-1);
	if (ln.exp < LN_EXP_SHIFT)
		return ((unsigned long)0);
	ul >>= shift;
	return (ul);
}

t_ln			ldtoln(long double ld)
{
	t_ln		ln;
	t_ld		u_ld;

	u_ld.ld = ld;
	ft_bzero(&ln, sizeof(ln));
	ln.exp = u_ld.s_ld.e - LD_EXP_SHIFT + LN_EXP_SHIFT;
	ln.mnt[LN_SIZE - 1] = u_ld.s_ld.m;
	return (ln);
}
