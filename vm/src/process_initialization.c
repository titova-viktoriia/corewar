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

void		create_new_process(int id, int pc, t_corewar *corewar)
{
	t_process	*process;

	if (!(process = (t_process *)malloc(sizeof(t_process))))
		terminate(corewar, "Произошла ошибка при инитиализации");
	process->uid = id;
	process->pc = pc;
	process->pc_buffer = 0;
	process->flag_carry = 0;
	process->cycle_before_execution = 0;
	process->last_live_operation_cycle = 0;
	process->operations_code = 0;
	process->registers[0] = -id;
	process->args_validation = 1;
	process->next = corewar->processes;
	corewar->processes = process;
	corewar->processes_number++;
}

void		process_initialization(t_corewar *corewar)
{
	int		i;
	int		pc;

	i = 0;
	pc = 0;
	while (i < corewar->players_count)
	{
		corewar->process_id_counter++;
		create_new_process(corewar->process_id_counter, pc, corewar);
		pc += MEM_SIZE / corewar->players_count;
		i++;
	}
}
