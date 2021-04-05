/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:32:44 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:33:47 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

void	data_print(t_data *data)
{
	t_instruction	*current;
	unsigned		i;

	ft_dprintf(data->fd, ".name \"%s\"\n", data->name);
	ft_dprintf(data->fd, ".comment \"%s\"\n\n", data->comment);
	current = data->instructions;
	while (current)
	{
		ft_dprintf(data->fd, "%s", current->op->name);
		i = 0;
		while (i < current->op->args_num)
		{
			if (current->args_types[i] == T_DIR)
				ft_dprintf(data->fd, " %%%ld", (long)current->args[i]);
			else if (current->args_types[i] == T_IND)
				ft_dprintf(data->fd, " %ld", (long)current->args[i]);
			else if (current->args_types[i] == T_REG)
				ft_dprintf(data->fd, " r%ld", (long)current->args[i]);
			if (i < current->op->args_num - 1)
				ft_dprintf(data->fd, ",");
			i++;
		}
		ft_dprintf(data->fd, "\n");
		current = current->next;
	}
}
