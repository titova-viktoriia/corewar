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

t_process	*delete_process(int process_to_delete_uid, t_process *processes)
{
	t_process *previous_process;
	t_process *current_process;
	t_process *head_process;

	previous_process = NULL;
	current_process = processes;
	head_process = processes;
	while (current_process)
	{
		if (current_process->uid == process_to_delete_uid)
		{
			if (previous_process == NULL)
				head_process = current_process->next;
			else
				previous_process->next = current_process->next;
			free(current_process);
			break ;
		}
		previous_process = current_process;
		current_process = current_process->next;
	}
	return (head_process);
}

void		set_process_args_type(t_process *process, t_corewar *corewar)
{
	int8_t		argument;
	t_op		*operation;
	int			i;

	i = 0;
	operation = &g_ops[process->operations_code - 1];
	argument = get_one_byte(corewar->arena, process->pc + 1);
	if (operation->args_types_code == 0)
	{
		process->args[0] = operation->args_types[0];
		return ;
	}
	while (i < operation->args_number)
	{
		if (i == 0 && !(process->args[0] =
				get_type_code((int8_t)((argument & 0xC0) >> 6))))
			process->args_validation = 0;
		if (i == 1 && !(process->args[1] =
				get_type_code((int8_t)((argument & 0x30) >> 4))))
			process->args_validation = 0;
		if (i == 2 && !(process->args[2] =
				get_type_code((int8_t)((argument & 0xC) >> 2))))
			process->args_validation = 0;
		i++;
	}
}

void		set_operation(t_process *process, t_corewar *corewar)
{
	process->operations_code = corewar->arena[process->pc];
	if (check_if_operation_exists(process->operations_code))
		process->cycle_before_execution =
				g_ops[process->operations_code - 1].cycles_before_execution;
}

void		reset_process(t_process *process)
{
	process->pc = get_pc(process->pc_buffer);
	process->args_validation = 1;
	process->pc_buffer = 0;
	ft_bzero(process->args, 3);
}

t_process	*duplicate_process(t_process *parent, int uid, t_corewar *corewar)
{
	t_process	*process;

	if (!(process = (t_process *)malloc(sizeof(t_process))))
		terminate(corewar, "Произошла ошибка при инитиализации");
	process->uid = uid;
	process->pc = 0;
	process->flag_carry = parent->flag_carry;
	process->cycle_before_execution = 0;
	process->pc_buffer = 0;
	process->last_live_operation_cycle = parent->last_live_operation_cycle;
	process->operations_code = 0;
	copy_registers(process, parent);
	process->args_validation = 1;
	process->next = NULL;
	return (process);
}
