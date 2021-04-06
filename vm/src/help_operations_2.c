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

int			get_pc(int pc)
{
	int result;

	result = pc % MEM_SIZE;
	if (result < 0)
		result += MEM_SIZE;
	return (result);
}

int32_t		get_int32_from_arena(const uint8_t *arena, int pc, int size)
{
	int32_t		int32_format;
	int			sign;
	int			i;
	int			current_pc;

	i = 0;
	sign = 0;
	int32_format = 0;
	current_pc = get_pc(pc);
	if (arena[pc % MEM_SIZE] & 0x80)
		sign = 1;
	while (size)
	{
		pc = get_pc(current_pc + size - 1);
		if (sign)
			int32_format += ((arena[pc] ^ 0xFF) << (i++ * 8));
		else
			int32_format += arena[pc] << (i++ * 8);
		size--;
	}
	if (sign)
		int32_format = ~(int32_format);
	return (int32_format);
}

int32_t		get_t_ind_value(const uint8_t *arena, int current_pc, int pc)
{
	int32_t		address;
	int32_t		value;

	address = get_int32_from_arena(arena, current_pc, IND_SIZE);
	address %= IDX_MOD;
	address = get_pc(pc + address);
	value = get_int32_from_arena(arena, address, REG_SIZE);
	return (value);
}

int32_t		get_t_ind_value_without_idx_mode(const uint8_t *arena,
												int current_pc, int pc)
{
	int32_t		address;
	int32_t		value;

	address = get_int32_from_arena(arena, current_pc, IND_SIZE);
	address %= IDX_MOD;
	address = get_pc(pc + address);
	value = get_int32_from_arena(arena, address, REG_SIZE);
	return (value);
}

void		set_int32_t_value_on_arena(int32_t value,
										int32_t pc,
										t_corewar *corewar)
{
	int8_t	i;
	int		size;
	int		current_pc;

	i = 0;
	size = 4;
	current_pc = get_pc(pc);
	while (size)
	{
		pc = get_pc(current_pc + size - 1);
		corewar->arena[pc] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}
