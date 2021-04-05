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

void		op_st(t_process *process, t_corewar *corewar)
{
	int			current_pc;
	int8_t		register_number;
	int32_t		register_value;
	int32_t		t_ind_value;

	current_pc = process->pc + 2;
	register_number = get_one_byte(corewar->arena, current_pc);
	register_value = process->registers[register_number - 1];
	current_pc++;
	if (process->args[1] == T_IND)
	{
		t_ind_value = get_int32_from_arena(corewar->arena,
											current_pc, IND_SIZE);
		t_ind_value %= IDX_MOD;
		t_ind_value = get_pc(process->pc + t_ind_value);
		set_int32_t_value_on_arena(register_value, t_ind_value, corewar);
	}
	if (process->args[1] == T_REG)
	{
		register_number = get_one_byte(corewar->arena, current_pc);
		process->registers[register_number - 1] = register_value;
	}
}
