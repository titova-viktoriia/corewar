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

void		check_if_process_is_died(t_process *process, t_corewar *corewar)
{
	if (corewar->cycles_to_die <= 0 ||
		corewar->total_cycles_number - process->last_live_operation_cycle >=
		corewar->cycles_to_die)
	{
		//debug
		ft_printf("CYCLE FOR DEAD: %d. ", corewar->total_cycles_number);
		ft_printf("DELETE PROCESS: %d \n", process->uid);
		//
		corewar->processes = delete_process(process->uid, corewar->processes);
		corewar->processes_number--;
	}
}

void		check_died_processes(t_corewar *corewar)
{
	t_process	*current_process;
	t_process	*next_process;

	current_process = corewar->processes;
	while (current_process)
	{
		next_process = current_process->next;
		check_if_process_is_died(current_process, corewar);
		current_process = next_process;
	}
	corewar->die_check_counter++;
	reduce_cycles_to_die(corewar);
	corewar->current_cycle = 0;
	reset_player_live(corewar);
}

void		check_process(t_process *process, t_corewar *corewar)
{
	if (process->cycle_before_execution == 0)
		set_operation(process, corewar);
	if (process->cycle_before_execution > 0)
		process->cycle_before_execution--;
	if (process->cycle_before_execution == 0)
	{
		if (check_if_operation_exists(process->operations_code))
		{
			set_process_args_type(process, corewar);
			check_process_args_type(process);
			check_arguments(process, corewar);
			if (process->args_validation == 1) {

				//debug
				ft_printf("Cycle %d, Process %d, Operation %s\n",
						  corewar->total_cycles_number, process->uid, g_ops[process->operations_code - 1].operation_name  );

				g_ops[process->operations_code - 1].function(process, corewar);


			}
		}
		else
			process->pc_buffer = process->pc + 1;
		reset_process(process);
	}
}

void		check_all_processes(t_corewar *corewar)
{
	t_process	*current_process;

	current_process = corewar->processes;
	while (current_process)
	{
		check_process(current_process, corewar);
		current_process = current_process->next;
	}
}
