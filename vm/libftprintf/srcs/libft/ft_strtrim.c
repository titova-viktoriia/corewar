/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:15:06 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_beginning(char const *s)
{
	int		i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static int	check_ending(char const *s)
{
	int		i;
	int		k;
	int		res;

	res = 0;
	i = ft_strlen(s);
	k = i;
	while ((s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t') && res < k)
	{
		res++;
		i--;
	}
	return (res);
}

char		*ft_strtrim(char const *s)
{
	int		len;
	int		end;
	int		begin;
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	end = check_ending(s);
	begin = check_beginning(s);
	if (len == end)
		end = 0;
	if (!(str = (char *)malloc(sizeof(char) * (len - end - begin + 1))))
		return (NULL);
	while (i < len - end - begin)
	{
		str[i] = s[i + begin];
		i++;
	}
	str[i] = '\0';
	return (str);
}
