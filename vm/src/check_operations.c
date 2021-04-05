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

int			check_register(int8_t argument)
{
	if (argument < 1 || argument > REG_NUMBER)
		return (0);
	return (1);
}

int			add_step(uint8_t argument, t_op *operation)
{
	int		step;

	step = 0;
	if (argument == T_REG)
		step = T_REG;
	if (argument == T_IND)
		step = IND_SIZE;
	if (argument == T_DIR)
		step = operation->t_dir_size;
	return (step);
}

void		check_arguments(t_process *process, t_corewar *corewar)
{
	int		i;
	int		arena_index;
	t_op	*operation;

	i = 0;
	operation = &g_ops[process->operations_code - 1];
	arena_index = process->pc + 1;
	if (operation->args_types_code)
		arena_index++;
	while (i < operation->args_number)
	{
		if (process->args[i] == T_REG &&
			!check_register(get_one_byte(corewar->arena, arena_index)))
			process->args_validation = 0;
		arena_index += add_step(process->args[i], operation);
		i++;
	}
	process->pc_buffer = arena_index;
}

int			check_if_operation_exists(uint8_t operations_code)
{
	if (operations_code >= 0x01 && operations_code <= 0x10)
		return (1);
	return (0);
}

void		check_process_args_type(t_process *process)
{
	int		i;
	t_op	*operation;

	i = 0;
	operation = &g_ops[process->operations_code - 1];
	while (i < operation->args_number)
	{
		if (!(process->args[i] & operation->args_types[i]))
			process->args_validation = 0;
		i++;
	}
}
