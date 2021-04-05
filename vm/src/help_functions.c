/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			ft_isnumber(char *str)
{
	int		i;

	i = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			ft_strncmp_end(char *str, char *end)
{
	int i;
	int i_end;
	int str_len;
	int end_len;

	i_end = 0;
	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len > str_len)
		return (0);
	i = str_len - end_len;
	while (str[i] != '\0')
	{
		if (str[i] != end[i_end])
			return (0);
		i++;
		i_end++;
	}
	return (1);
}

int8_t		get_one_byte(uint8_t *arena, int pc)
{
	int index;

	index = pc % MEM_SIZE;
	if (index < 0)
		index += MEM_SIZE;
	return (arena[index]);
}

int			get_type_code(int8_t argument_type)
{
	if (argument_type == REG_CODE)
		return (T_REG);
	if (argument_type == DIR_CODE)
		return (T_DIR);
	if (argument_type == IND_CODE)
		return (T_IND);
	return (0);
}

int			find_number(int i, const int *nums, int size)
{
	int		result;

	i = 0;
	result = nums[0];
	while (i < size)
	{
		if (nums[i] < result)
			result = nums[i];
		i++;
	}
	result++;
	while (!check_dublicates(result, nums))
		result++;
	return (result);
}
