/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:58:17 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*str;

	if (size + 1 == 0)
		return (NULL);
	if (size == 0)
		return (NULL);
	str = ft_memalloc(size + 1);
	if (!(str))
		return (NULL);
	return (str);
}
