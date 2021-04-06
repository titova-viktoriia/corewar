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

void		reduce_cycles_to_die(t_corewar *corewar)
{
	if (corewar->operation_live_number >= NBR_LIVE ||
		corewar->die_check_counter == MAX_CHECKS)
	{
		corewar->cycles_to_die -= CYCLE_DELTA;
		corewar->die_check_counter = 0;
	}
}

void		execution(t_corewar *corewar)
{
	while (corewar->processes_number != 0) {
		if ((corewar->dump_flag == 1 || corewar->d_flag == 1) &&
			corewar->dump_cycles == corewar->total_cycles_number)
		{
			print_arena(corewar);
			return ;
		}
		corewar->total_cycles_number++;
		corewar->current_cycle++;

		//debug
		if (corewar->total_cycles_number == 11005 ||
			corewar->total_cycles_number == 2725)
			ft_printf("CYCLE: %d .\n", corewar->total_cycles_number);

		check_all_processes(corewar);
		if (corewar->current_cycle == corewar->cycles_to_die
			|| corewar->cycles_to_die <= 0)
		{
			check_died_processes(corewar);
		}
	}
}
