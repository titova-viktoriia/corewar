/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:40:44 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/25 06:27:50 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"

void	print_error(t_data *data)
{
	ft_dprintf(2, "Error at [%03u:%03u]\n", data->row,
			data->column + 1);
	exit(1);
}

void	wrong_token(t_token *token)
{
	ft_dprintf(2, "Wrong %s token \"%s\" at [%03u:%03u]\n",
			g_type[token->type], token->content,
			token->row, token->column + 1);
	exit(1);
}

void	wrong_label(t_label *label)
{
	t_lab_pos	*lab_pos;

	ft_dprintf(2, "Wrong label \"%s\" at:\n", label->name);
	lab_pos = label->lab_sublist;
	while (lab_pos)
	{
		ft_dprintf(2, "\t— [%03u:%03u]\n", lab_pos->row, lab_pos->column + 1);
		lab_pos = lab_pos->next;
	}
	exit(1);
}
