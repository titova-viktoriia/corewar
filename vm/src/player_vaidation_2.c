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

void		reset_player_live(t_corewar *corewar)
{
	int		i;

	i = 0;
	while (i < corewar->players_count)
	{
		corewar->players[i].previous_lives_number =
				corewar->players[i].current_lives_number;
		corewar->players[i].current_lives_number = 0;
		i++;
	}
	corewar->operation_live_number = 0;
}

void		update_players_numbers(t_corewar *corewar)
{
	int		i;

	i = 0;
	while (i < corewar->players_count)
	{
		if (corewar->players_number_buffer[i] > corewar->players_count)
			terminate(corewar,
			"Номер игрока не может быть больше количества игроков\n");
		if (corewar->players_number_buffer[i] == 0)
			corewar->players_number_buffer[i] =
					find_number(i, corewar->players_number_buffer,
					corewar->players_count);
		i++;
	}
}

int			get_player_index_from_buffer(int index, const int *buffer)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (buffer[i] == index)
			return (i);
		i++;
	}
	return (-1);
}

void		init_player(t_player *player, int id)
{
	player->id = id + 1;
	player->name = NULL;
	player->comment = NULL;
	player->code = NULL;
	player->size = 0;
	player->last_live = 0;
	player->current_lives_number = 0;
	player->previous_lives_number = 0;
}

int32_t		from_bytecode_to_int32(const uint8_t *bytecode, size_t size)
{
	int32_t		int32_format;
	int			sign;
	int			i;

	i = 0;
	sign = 0;
	int32_format = 0;
	if (bytecode[0] & 0x80)
		sign = 1;
	while (size)
	{
		if (sign)
			int32_format += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			int32_format += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		int32_format = ~(int32_format);
	return (int32_format);
}
