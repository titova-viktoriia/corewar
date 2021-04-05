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

void		init_players_number_buffer(t_corewar *corewar)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		corewar->players_number_buffer[i] = 0;
		i++;
	}
}

t_corewar	*corewar_initialization(void)
{
	t_corewar	*corewar;

	if (!(corewar = (t_corewar *)malloc(sizeof(t_corewar))))
		return (NULL);
	corewar->processes = NULL;
	corewar->processes_number = 0;
	corewar->cycles_to_die = CYCLE_TO_DIE;
	corewar->total_cycles_number = 0;
	corewar->operation_live_number = 0;
	corewar->die_check_counter = 0;
	corewar->current_cycle = 0;
	corewar->process_id_counter = 0;
	corewar->dump_flag = 0;
	corewar->d_flag = 0;
	corewar->live_flag = 0;
	corewar->dump_cycles = 0;
	init_players_number_buffer(corewar);
	corewar->players_count = 0;
	corewar->players_init_count = 0;
	return (corewar);
}
