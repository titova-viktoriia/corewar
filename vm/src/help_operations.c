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

int32_t	get_value_from_register(t_corewar *corewar, t_process *process, int pc)
{
	int8_t		register_number;

	register_number = get_one_byte(corewar->arena, pc);
	//debug
	//ft_printf("reg_num - %d\n", register_number );
	//
	return (process->registers[register_number - 1]);
}

int32_t	get_int32_t_argument(t_corewar *corewar,
							t_process *process,
							int arg_index, int current_pc)
{
	int32_t		result;
	int			argument;

	argument = process->args[arg_index];
	if (argument & T_REG)
		result = get_value_from_register(corewar, process, current_pc);
	if (argument & T_DIR)
		result = get_int32_from_arena(corewar->arena, current_pc, DIR_SIZE_4);
	if (argument & T_IND)
		result = get_t_ind_value(corewar->arena, current_pc, process->pc);
	return (result);
}

int32_t	get_int32_t_argument_2(t_corewar *corewar,
								t_process *process,
								int arg_index, int current_pc)
{
	int32_t		result;
	int			argument;

	argument = process->args[arg_index];
	if (argument & T_REG)
		result = get_value_from_register(corewar, process, current_pc);
	if (argument & T_DIR)
		result = get_int32_from_arena(corewar->arena, current_pc, DIR_SIZE_2);
	if (argument & T_IND)
		result = get_t_ind_value(corewar->arena, current_pc, process->pc);
	return (result);
}

void	copy_registers(t_process *new, t_process *parent)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		new->registers[i] = parent->registers[i];
		i++;
	}
}
