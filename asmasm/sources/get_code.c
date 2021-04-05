/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 06:34:41 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/27 09:01:43 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_op.h"
#include "dasm.h"
#include "ft_printf.h"

static void		convert_labels(t_data *data)
{
	t_label		*label;
	t_lab_pos	*lab_pos;

	label = data->labels;
	while (label)
	{
		if (label->op_pos == -1)
			wrong_label(label);
		else
		{
			lab_pos = label->lab_sublist;
			while (lab_pos)
			{
				if (lab_pos->size == 2)
					get_bytecode(data->code, lab_pos->pos,
							(int16_t)(label->op_pos - lab_pos->op_pos), 2);
				else
					get_bytecode(data->code, lab_pos->pos,
							label->op_pos - lab_pos->op_pos, lab_pos->size);
				lab_pos = lab_pos->next;
			}
		}
		label = label->next;
	}
}

static void		get_label(t_data *data)
{
	t_label	*label;
	char	*name;

	if (!(name = ft_strsub(data->token->content,
					0, ft_strlen(data->token->content) - 1)))
		ft_throw("ERROR: Can not initialize string");
	if (!(label = find_label(data->labels, name)))
		add_label(&(data->labels), new_label(name, data->op_pos));
	if (label && label->op_pos == -1)
		label->op_pos = data->pos;
	ft_strdel(&name);
}

static void		get_operator(t_data *data)
{
	t_op		*op;
	int8_t		types_byte;
	unsigned	i;

	i = 0;
	while (i < (sizeof(g_op) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op[i].name, data->token->content))
		{
			op = &g_op[i];
			data->code[data->pos++] = op->code;
			data->token = data->token->next;
			if (op->args_types_byte)
				data->pos++;
			types_byte = get_args_types(data, op);
			if (op->args_types_byte)
				data->code[data->op_pos + 1] = types_byte;
			return ;
		}
		i++;
	}
	ft_dprintf(2, "Wrong operator \"%s\" at [%03u:%03u]\n",
			data->token->content,
			data->token->row, data->token->column + 1);
	exit(1);
}

void			get_code(t_data *data)
{
	while (data->token->type != END)
	{
		if (data->pos >= data->code_size)
		{
			data->code_size += CHAMP_MAX_SIZE;
			if (!(data->code = (char *)realloc(data->code,
							((size_t)data->code_size + 14))))
				ft_throw("ERROR: Can not initialize string");
		}
		data->op_pos = data->pos;
		if (data->token->type == LABEL)
		{
			get_label(data);
			data->token = data->token->next;
		}
		if (data->token->type == OPERATOR)
			get_operator(data);
		if (data->token->type == NEW_LINE)
			data->token = data->token->next;
		else
			wrong_token(data->token);
	}
	convert_labels(data);
}
