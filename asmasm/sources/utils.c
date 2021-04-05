/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:46:38 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/27 09:04:39 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "dasm.h"

void		ft_throw(char *s)
{
	errno ? perror(s) : ft_putendl_fd(s, 2);
	exit(1);
}

void		get_bytecode(char *code, int32_t pos, int32_t value, size_t size)
{
	int8_t		i;

	i = 0;
	while (size)
	{
		code[pos + size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

t_lab_pos	*new_lab_pos(t_data *data, t_token *token, size_t size)
{
	t_lab_pos	*lab_pos;

	if (!(lab_pos = (t_lab_pos *)ft_memalloc(sizeof(t_lab_pos))))
		ft_throw("ERROR: Can not initialize lab_pos");
	lab_pos->row = token->row;
	lab_pos->column = token->column;
	lab_pos->pos = data->pos;
	lab_pos->op_pos = data->op_pos;
	lab_pos->size = size;
	lab_pos->next = NULL;
	return (lab_pos);
}

void		add_lab_pos(t_lab_pos **list, t_lab_pos *new)
{
	t_lab_pos	*current;

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
