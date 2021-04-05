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

void		op_sub(t_process *process, t_corewar *corewar)
{
	int8_t		register_1;
	int8_t		register_2;
	int8_t		register_3;
	int			current_pc;
	int32_t		result;

	current_pc = process->pc + 2;
	register_1 = get_one_byte(corewar->arena, current_pc);
	current_pc++;
	register_2 = get_one_byte(corewar->arena, current_pc);
	current_pc++;
	register_3 = get_one_byte(corewar->arena, current_pc);
	result = process->registers[register_1 - 1] -
			process->registers[register_2 - 1];
	process->registers[register_3 - 1] = result;
	if (result == 0)
		process->flag_carry = 1;
	else
		process->flag_carry = 0;
}
