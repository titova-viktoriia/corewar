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

void		op_lfork(t_process *process, t_corewar *corewar)
{
	int32_t		argument;
	int			current_pc;
	t_process	*new_process;

	current_pc = process->pc + 1;
	argument = get_int32_from_arena(corewar->arena, current_pc, DIR_SIZE_2);
	new_process = duplicate_process(process,
						corewar->process_id_counter++, corewar);
	new_process->pc = get_pc(process->pc + argument);
	new_process->next = corewar->processes;
	corewar->processes = new_process;
	corewar->processes_number++;
}
