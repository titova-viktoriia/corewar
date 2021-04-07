/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/04/07 21:24:55 by cport            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_zjmp(t_process *process, t_corewar *corewar)
{
	int32_t	value;
	int		current_pc;

	current_pc = process->pc + 1;
	value = get_int32_from_arena(corewar->arena, current_pc, DIR_SIZE_2);
	if (process->flag_carry)
		process->pc_buffer = get_pc(process->pc + (value % IDX_MOD));
}
