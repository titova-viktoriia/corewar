/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:13:15 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	i = -1;
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (len == 0 || dst == src)
		return (dst);
	if (a > b)
	{
		while ((int)--len >= 0)
			*(a + len) = *(b + len);
	}
	else
	{
		while (++i < len)
			*(a + i) = *(b + i);
	}
	return (dst);
}
