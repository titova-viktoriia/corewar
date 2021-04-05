/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		arena_initialization(t_corewar *corewar)
{
	int		i;
	int		arena_index;

	i = 0;
	arena_index = 0;
	ft_bzero(&(corewar->arena), MEM_SIZE);
	while (i < corewar->players_count)
	{
		ft_memcpy(&(corewar->arena[arena_index]),
			corewar->players[i].code,
			corewar->players[i].size);
		arena_index += MEM_SIZE / corewar->players_count;
		i++;
	}
}
