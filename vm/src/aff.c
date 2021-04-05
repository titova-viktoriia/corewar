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

void		op_aff(t_process *process, t_corewar *corewar)
{
	int			current_pc;
	int8_t		register_number;
	int32_t		register_value;

	current_pc = process->pc + 2;
	register_number = get_one_byte(corewar->arena, current_pc);
	register_value = process->registers[register_number - 1];
	ft_printf("Aff - %c\n", (char)register_value);
}
