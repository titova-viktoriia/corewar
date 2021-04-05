/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:35:54 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	char			*a;
	unsigned int	len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	a = (char *)s;
	i = 0;
	len = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, *a);
		i++;
		a++;
	}
	str[i] = '\0';
	return (str);
}
