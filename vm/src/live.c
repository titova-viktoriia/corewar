/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_live(t_process *process, t_corewar *corewar)
{
	int32_t		argument;
	int			current_pc;

	current_pc = process->pc + 1;
	argument = get_int32_from_arena(corewar->arena, current_pc, DIR_SIZE_4);
	if (argument <= -1 && argument >= -(corewar->players_count))
	{
		argument *= -1;
		corewar->players[argument - 1].last_live = corewar->total_cycles_number;
		corewar->players[argument - 1].current_lives_number++;
		corewar->last_live_player = corewar->players[argument - 1].id;
		if (corewar->live_flag == 1)
			ft_printf("A process shows that player %d (%s) is alive”.\n",
				corewar->players[argument - 1].id,
				corewar->players[argument - 1].name);
	}
	corewar->operation_live_number++;
	process->last_live_operation_cycle = corewar->total_cycles_number;
}
