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

void		op_ld(t_process *process, t_corewar *corewar)
{
	int8_t		register_number;
	int32_t		register_value;
	int			arena_index;

	arena_index = process->pc + 2;
	if (process->args[0] == T_DIR)
		register_value = get_int32_from_arena(corewar->arena,
										arena_index, DIR_SIZE_4);
	if (process->args[0] == T_IND)
		register_value = get_t_ind_value(corewar->arena,
										arena_index, process->pc);
	if (register_value == 0)
		process->flag_carry = 1;
	else
		process->flag_carry = 0;
	if (process->args[0] == T_DIR)
		arena_index += (DIR_SIZE_4);
	if (process->args[0] == T_IND)
		arena_index += (IND_SIZE);
	register_number = get_one_byte(corewar->arena, arena_index);
	process->registers[register_number - 1] = register_value;
}
