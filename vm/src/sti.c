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

void		op_sti(t_process *process, t_corewar *corewar)
{
	int32_t		argument_1;
	int32_t		argument_2;
	int32_t		register_value;
	int			current_pc;

	current_pc = process->pc + 2;
	register_value = get_value_from_register(corewar, process, current_pc);
	current_pc++;
	current_pc = get_pc(current_pc);
	argument_1 = get_int32_t_argument_2(corewar, process, 1, current_pc);
	current_pc += add_step(process->args[1], &g_ops[11 - 1]);
	argument_2 = get_int32_t_argument_2(corewar, process, 2, current_pc);
	set_int32_t_value_on_arena(register_value,
		process->pc + ((argument_1 + argument_2) % IDX_MOD), corewar);
}
