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

void	set_player(char *file_name, t_corewar *corewar)
{
	if (corewar->players_count == MAX_PLAYERS)
		terminate(corewar,
			"Игроков не может быть больше значения MAX_PLAYERS\n");
	corewar->players_file_buffer[corewar->players_count] = file_name;
	corewar->players_count++;
}

void	set_dump_flag(char *flag, char *argv, int diff_argc, t_corewar *corewar)
{
	long long	number;

	if (corewar->d_flag != 0 || corewar->dump_flag != 0)
		terminate(corewar, "Флаг -d или -dump установлен повторно\n");
	if (diff_argc <= 1)
		terminate(corewar, "Не установлено значение -d/-dump флага\n");
	if (!ft_isnumber(argv))
		terminate(corewar, "Некорректное значение -d/-dump флага\n");
	number = ft_atoi_long_long(argv);
	if (number > 2147483647 || number < 0)
		terminate(corewar, "Некорректное значение -d/-dump флага\n");
	if ((ft_strcmp(flag, "-dump") == 0))
	{
		corewar->dump_flag = 1;
		corewar->dump_cycles = (int)number;
	}
	if ((ft_strcmp(flag, "-d") == 0))
	{
		corewar->d_flag = 1;
		corewar->dump_cycles = (int)number;
	}
}

int		check_dublicates(int num, const int *nums)
{
	int		i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (nums[i] == num)
			return (0);
		i++;
	}
	return (1);
}

void	set_player_number(int argc, char **argv, int i, t_corewar *corewar)
{
	long long number;

	if (argc - i <= 2)
		terminate(corewar, "Некорректно установлен флаг -n\n");
	if (!(ft_isnumber(argv[i + 1])))
		terminate(corewar, "Некорректное значение -n флага\n");
	number = ft_atoi_long_long(argv[i + 1]);
	if (number <= 0 || number > MAX_PLAYERS)
		terminate(corewar, "Значение -n не может быть < 0 и > MAX_PLAYER\n");
	if (corewar->players_count == MAX_PLAYERS)
		terminate(corewar, "Игроков не может быть > MAX_PLAYER\n");
	if (!check_dublicates((int)number, corewar->players_number_buffer))
		terminate(corewar, "Дублируются номера игроков\n");
	corewar->players_number_buffer[corewar->players_count] = (int)number;
	if (!ft_strncmp_end(argv[i + 2], ".cor"))
		terminate(corewar, "Некорректное имя файла\n");
	set_player(argv[i + 2], corewar);
}

void	parse_and_validate_args(int argc, char **argv,
									t_corewar *corewar, int i)
{
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-dump") == 0 || ft_strcmp(argv[i], "-d") == 0)
		{
			set_dump_flag(argv[i], argv[i + 1], argc - i, corewar);
			i += 2;
		}
		else if (ft_strcmp(argv[i], "-n") == 0)
		{
			set_player_number(argc, argv, i, corewar);
			i += 3;
		}
		else if (ft_strncmp_end(argv[i], ".cor"))
		{
			set_player(argv[i], corewar);
			i += 1;
		}
		else if (ft_strcmp(argv[i], "-show") == 0)
		{
			corewar->live_flag = 1;
			i += 1;
		}
		else
			terminate(corewar, "Некорректный формат\n");
	}
}
