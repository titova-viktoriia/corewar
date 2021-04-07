/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/04/07 21:29:41 by cport            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_ldi(t_process *process, t_corewar *corewar)
{
	int32_t		argument_1;
	int32_t		argument_2;
	int8_t		register_number;
	int32_t		result;
	int			current_pc;

	current_pc = process->pc + 2;
	argument_1 = get_int32_t_argument_2(corewar, process, 0, current_pc);
	current_pc += add_step(process->args[0], &g_ops[10 - 1]);
	argument_2 = get_int32_t_argument_2(corewar, process, 1, current_pc);
	current_pc += add_step(process->args[1], &g_ops[10 - 1]);
	register_number = get_one_byte(corewar->arena, current_pc);
	result = get_int32_from_arena(corewar->arena,
		process->pc + ((argument_1 + argument_2) % IDX_MOD),
		DIR_SIZE_4);
	process->registers[register_number - 1] = result;
}
