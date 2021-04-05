/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:40:44 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/25 18:43:11 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"

void	print_warning(size_t pos, size_t len)
{
	size_t	shift;

	if (len == PROG_NAME_LENGTH)
	{
		shift = 4;
		ft_dprintf(2, "Warning: Name has extra not null bytes at %u byte\n",
				shift + pos + 1);
	}
	else if (len == COMMENT_LENGTH)
	{
		shift = 4 + PROG_NAME_LENGTH + 4 + 4;
		ft_dprintf(2, "Warning: Comment has extra not null bytes"
				" at %u byte\n", shift + pos + 1);
	}
	else
	{
		shift = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
		ft_dprintf(2, "Warning: Extra bits in code of arguments types are"
				" not null at %u byte\n", shift + pos + 1);
	}
}

void	print_error(t_data *data, char *err)
{
	size_t	shift;

	shift = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	ft_dprintf(2, "ERROR: %s at %u byte\n", err, shift + data->pos);
	exit(0);
}
