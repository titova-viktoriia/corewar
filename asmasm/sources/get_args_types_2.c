/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_types_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 06:37:16 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/25 06:51:42 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"

static int32_t		ft_atoi32(const char *str)
{
	unsigned long	result;
	unsigned long	border;
	size_t			i;
	int				sign;

	result = 0;
	border = (unsigned long)((long)((unsigned long)(~0L) >> 1) / 10);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if ((result > border || (result == border && (str[i] - '0') > 7))
				&& sign == 1)
			return (-1);
		else if ((result > border || (result == border && (str[i] - '0') > 8))
				&& sign == -1)
			return (0);
		result = result * 10 + (str[i++] - '0');
	}
	return ((int32_t)(result * sign));
}

void				get_numbers_bytecode(t_data *data, t_op *op)
{
	unsigned	start;
	size_t		size;

	start = (data->token->type == DIRECT) ? 1 : 0;
	size = (data->token->type == DIRECT) ? op->t_dir_size : IND_SIZE;
	if (size == 2)
		get_bytecode(data->code, data->pos,
				(int16_t)ft_atoi32(&data->token->content[start]), size);
	else
		get_bytecode(data->code, data->pos,
				ft_atoi32(&data->token->content[start]), size);
	data->pos += size;
}

t_label				*new_label(char *name, int op_pos)
{
	t_label	*label;

	if (!(label = (t_label *)ft_memalloc(sizeof(t_label))))
		ft_throw("ERROR: Can not initialize label");
	if (!(label->name = ft_strdup(name)))
		ft_throw("ERROR: Can not initialize string");
	label->op_pos = op_pos;
	label->lab_sublist = NULL;
	label->next = NULL;
	return (label);
}

void				add_label(t_label **list, t_label *new)
{
	t_label	*current;

	if (list)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

t_label				*find_label(t_label *list, char *name)
{
	t_label	*label;

	label = list;
	while (label)
	{
		if (!ft_strcmp(label->name, name))
			return (label);
		label = label->next;
	}
	return (label);
}
