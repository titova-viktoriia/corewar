/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:37:21 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:40:18 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"

static uint8_t		get_arg_type(int8_t code)
{
	if (code == DIR_CODE)
		return (T_DIR);
	else if (code == REG_CODE)
		return (T_REG);
	else if (code == IND_CODE)
		return (T_IND);
	else
		return (0);
}

static int			check_args_types(t_instruction *instruction)
{
	int32_t i;

	i = 0;
	while (i < instruction->op->args_num)
	{
		if (!(instruction->args_types[i] & instruction->op->args_types[i]))
			return (0);
		i++;
	}
	return (1);
}

static void			check_args_types_code(t_data *data, int8_t args_types_code,
		int args_num)
{
	int		arg_num;
	int8_t	type;

	arg_num = 4;
	while (arg_num > args_num)
	{
		type = (int8_t)((args_types_code >> (2 * (4 - arg_num))) & 0x3);
		if (type != 0)
		{
			print_warning((size_t)data->pos, 0);
			return ;
		}
		arg_num--;
	}
}

int					get_args_types(t_data *data, t_instruction *instruction)
{
	int8_t args_types_code;

	if (instruction->op->args_types_code)
	{
		args_types_code = data->code[data->pos];
		if (instruction->op->args_num >= 1)
			instruction->args_types[0] =
						get_arg_type((int8_t)((args_types_code & 0xC0) >> 6));
		if (instruction->op->args_num >= 2)
			instruction->args_types[1] =
						get_arg_type((int8_t)((args_types_code & 0x30) >> 4));
		if (instruction->op->args_num >= 3)
			instruction->args_types[2] =
						get_arg_type((int8_t)((args_types_code & 0xC) >> 2));
		check_args_types_code(data, args_types_code, instruction->op->args_num);
	}
	else
		instruction->args_types[0] = instruction->op->args_types[0];
	return (check_args_types(instruction));
}
