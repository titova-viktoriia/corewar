/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pole_and_bufferdata.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:15:58 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 18:17:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		**ft_new_ar_c(int a, int b)
{
	char	**mas;
	int		i;

	mas = (char **)malloc(sizeof(char*) * (a));
	i = 0;
	while (i < a)
	{
		mas[i] = (char *)malloc(sizeof(char) * b);
		i++;
	}
	return (mas);
}
