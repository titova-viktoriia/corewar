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

int32_t		read_int32(int fd, t_corewar *corewar)
{
	int		readed;
	uint8_t	tmp[4];

	readed = read(fd, &tmp, 4);
	if (readed < 0)
		terminate(corewar, "Ошибка при чтении файла");
	if (readed < 4)
		terminate(corewar, "Неправильный 1");
	return (from_bytecode_to_int32(tmp, 4));
}

char		*parse_str(int fd, int size, t_corewar *corewar)
{
	int		readed;
	char	*buffer;

	if (!(buffer = ft_strnew(size)))
		terminate(corewar, "Ошибка при чтении файла");
	readed = read(fd, buffer, size);
	if (readed < 0)
		terminate(corewar, "Ошибка при чтении файла");
	if (readed < size)
		terminate(corewar, "Неправильный файл2");
	return (buffer);
}

uint8_t		*read_code(int fd, int size, t_corewar *corewar)
{
	int			readed;
	uint8_t		*tmp;
	uint8_t		byte;

	if (!(tmp = malloc(size)))
		terminate(corewar, "Ошибка чтения файла");
	readed = read(fd, tmp, size);
	if (readed < 0)
	{
		free(tmp);
		terminate(corewar, "Ошибка чтения файла");
	}
	if (readed < size || read(fd, &byte, 1) != 0)
	{
		free(tmp);
		terminate(corewar, "Неправильный файл3");
	}
	return (tmp);
}

void		read_and_validate_file(int i, int player_index, t_corewar *corewar)
{
	t_player	player;
	int			fd;

	init_player(&player, i);
	corewar->players_init_count++;
	corewar->players[i] = player;
	if ((fd = open(corewar->players_file_buffer[player_index], O_RDONLY)) < 0)
		terminate(corewar, "Ошибка чтения файла");
	if (read_int32(fd, corewar) != COREWAR_EXEC_MAGIC)
		terminate(corewar, ft_strjoin("Неправильный заголовок у файла ",
							corewar->players_file_buffer[player_index]));
	corewar->players[i].name = parse_str(fd, PROG_NAME_LENGTH, corewar);
	if (read_int32(fd, corewar) != 0)
		terminate(corewar, ft_strjoin("Нет нулевых контрольных байтов у ",
							corewar->players_file_buffer[player_index]));
	corewar->players[i].size = read_int32(fd, corewar);
	if (corewar->players[i].size < 0
			|| corewar->players[i].size > CHAMP_MAX_SIZE)
		terminate(corewar, "Некорректный размер кода игрока");
	corewar->players[i].comment = parse_str(fd, COMMENT_LENGTH, corewar);
	if (read_int32(fd, corewar) != 0)
		terminate(corewar,
			ft_strjoin("Отсутствуют нулевые контрольные байты у файла ",
					corewar->players_file_buffer[player_index]));
	corewar->players[i].code = read_code(fd, corewar->players[i].size, corewar);
}

void		validate_players(t_corewar *corewar)
{
	int i;
	int player_index_from_buffer;

	i = 0;
	update_players_numbers(corewar);
	while (i < corewar->players_count)
	{
		player_index_from_buffer =
				get_player_index_from_buffer(i + 1,
								corewar->players_number_buffer);
		read_and_validate_file(i, player_index_from_buffer, corewar);
		i++;
	}
	corewar->last_live_player = corewar->players_count;
}
