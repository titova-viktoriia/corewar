/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:37:21 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/25 06:46:14 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"

static void		process_lab_pos(t_data *data, t_op *op)
{
	t_label		*label;
	char		*name;
	unsigned	start;
	size_t		size;

	start = (data->token->type == DIR_LAB) ? 2 : 1;
	size = (data->token->type == DIR_LAB) ? op->t_dir_size : IND_SIZE;
	if (!(name = ft_strsub(data->token->content,
					start, ft_strlen(data->token->content) - start)))
		ft_throw("ERROR: Can not initialize string");
	if (!(label = find_label(data->labels, name)))
	{
		label = new_label(name, -1);
		add_label(&(data->labels), label);
	}
	ft_strdel(&name);
	add_lab_pos(&label->lab_sublist, new_lab_pos(data, data->token, size));
	data->pos += size;
}

static int8_t	get_arg_type(t_type type)
{
	if (type == DIRECT || type == DIR_LAB)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIR_LAB)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}

static int8_t	get_arg_type_and_bytecode(t_data *data, t_op *op, int arg_num)
{
	int8_t	type;

	type = get_arg_type(data->token->type);
	if (!(op->args_types[arg_num] & type))
	{
		ft_dprintf(2, "Invalid type of parameter #%d for instruction \"%s\""\
				" at [%03u:%03u]\n",
				arg_num + 1, op->name,
				data->token->row, data->token->column + 1);
		exit(1);
	}
	if (data->token->type == INDIR_LAB || data->token->type == DIR_LAB)
		process_lab_pos(data, op);
	else if (data->token->type == INDIRECT || data->token->type == DIRECT)
		get_numbers_bytecode(data, op);
	else
	{
		get_bytecode(data->code, data->pos,
				(int8_t)ft_atoi(&data->token->content[1]), 1);
		data->pos += 1;
	}
	return (type);
}

static uint8_t	get_arg_code(int8_t type)
{
	if (type == T_DIR)
		return (DIR_CODE);
	else if (type == T_REG)
		return (REG_CODE);
	else
		return (IND_CODE);
}

int8_t			get_args_types(t_data *data, t_op *op)
{
	int		arg_num;
	int8_t	types_byte;
	int8_t	type;

	arg_num = 0;
	types_byte = 0;
	while (arg_num < op->args_num)
	{
		if (data->token->type >= REGISTER && data->token->type <= INDIR_LAB)
		{
			type = get_arg_type_and_bytecode(data, op, arg_num);
			types_byte |= (get_arg_code(type) << 2 * (4 - arg_num - 1));
			data->token = data->token->next;
		}
		else
			wrong_token(data->token);
		if (arg_num++ != op->args_num - 1)
		{
			if (data->token->type != SEPARATOR)
				wrong_token(data->token);
			data->token = data->token->next;
		}
	}
	return (types_byte);
}
