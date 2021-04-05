/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:46:02 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**my_free(char **arr)
{
	int			i;

	i = 0;
	if (!arr)
		return (NULL);
	while (*arr[i] != '\0')
	{
		free((char *)arr[i]);
		*arr[i] = 0;
	}
	arr = 0;
	return (NULL);
}

static	int		word_count(char const *s, char c)
{
	int			i;
	int			words;

	i = 0;
	words = 0;
	if (s[i] != '\0' && s[i] != c)
		words = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

static int		word_len(char const *s, char c)
{
	int			i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			j;
	char		**arr;

	i = 0;
	j = 0;
	if (!s || !(arr = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1))))
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			if (!(arr[i] = ft_strnew((word_len(s, c)))))
				return (my_free(arr));
			while (*s != c && *s != '\0')
				arr[i][j++] = (char)*s++;
			arr[i][j] = '\0';
			i++;
			j = 0;
		}
	}
	arr[i] = NULL;
	return (arr);
}
