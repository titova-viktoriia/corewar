/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:34:08 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/23 09:33:44 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_op.h"
#include "dasm.h"
#include "ft_printf.h"

static size_t			get_size(t_instruction *instruction, unsigned i)
{
	if (instruction->args_types[i] == T_REG)
		return (1);
	else if (instruction->args_types[i] == T_IND)
		return (IND_SIZE);
	else
		return (instruction->op->t_dir_size);
}

static void				get_arg(t_data *data,
		t_instruction *instruction,
		unsigned i)
{
	size_t size;

	size = get_size(instruction, i);
	if (data->code_size - data->pos >= (int32_t)size)
	{
		instruction->args[i] = get_int(&data->code[data->pos], size);
		data->pos += size;
		if (instruction->args_types[i] == T_REG && instruction->args[i] <= 0)
			print_error(data, "Wrong register's id");
	}
	else
		print_error(data, "No enough bytes");
}

static void				get_args(t_data *data, t_instruction *instruction)
{
	unsigned i;

	i = 0;
	while (i < instruction->op->args_num)
	{
		get_arg(data, instruction, i);
		i++;
	}
}

static t_instruction	*new_instruction(void)
{
	t_instruction	*instruction;

	if (!(instruction = (t_instruction *)ft_memalloc(sizeof(t_instruction))))
		ft_throw("ERROR: Can not initialize instruction");
	instruction->op = NULL;
	instruction->next = NULL;
	return (instruction);
}

t_instruction			*get_instruction(t_data *data)
{
	t_instruction	*instruction;
	uint8_t			opcode;

	instruction = new_instruction();
	opcode = data->code[data->pos];
	if (opcode >= 0x01 && opcode <= 0x10)
	{
		data->pos++;
		instruction->op = &g_op[opcode - 1];
		if (instruction->op->args_types_code && data->pos >= data->code_size)
			print_error(data, "No enough bytes");
		if (get_args_types(data, instruction))
		{
			if (instruction->op->args_types_code)
				data->pos++;
			get_args(data, instruction);
		}
		else
			print_error(data, "Wrong code of arguments types");
	}
	else
		print_error(data, "Wrong opcode");
	return (instruction);
}
