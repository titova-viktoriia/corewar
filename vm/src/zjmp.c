/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		op_zjmp(t_process *process, t_corewar *corewar)
{
	int32_t	value;
	int		current_pc;

	current_pc = process->pc + 1;
	value = get_int32_from_arena(corewar->arena, current_pc, DIR_SIZE_2);
	if (process->flag_carry) {
		ft_printf(" OK: %d \n", value);
		process->pc_buffer = get_pc(process->pc + (value % IDX_MOD));
	}

}
