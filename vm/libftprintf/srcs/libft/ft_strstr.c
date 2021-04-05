/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:00:47 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		k;
	int		d;

	i = 0;
	k = 0;
	d = ft_strlen(needle);
	if (d == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[k])
		{
			if (ft_strncmp(haystack + i, needle, d) == 0)
				return ((char *)(haystack + i));
			k = 0;
		}
		i++;
	}
	return (0);
}
