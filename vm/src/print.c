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

void		print_arena(t_corewar *corewar)
{
	int	i;
	int	y;
	int	step;

	i = 0;
	step = 32;
	if (corewar->d_flag == 1)
		step = 64;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		y = 0;
		while (y < step)
		{
			ft_printf("%.2x ", corewar->arena[i + y]);
			y++;
		}
		ft_printf("\n");
		i += step;
	}
}

void		print_rules(void)
{
	ft_printf("Example: ./corewar_help example_1.cor example_2.cor \n");
	ft_printf("Flag -n number sets the number of the next player: ");
	ft_printf("./corewar_help -n 2 example_1.cor \n");
	ft_printf("Flag -dump nbr_cycles at the end of nbr_cycles of executions, ");
	ft_printf("dump the memory on the standard output and quit the game.\n");
}

void		hello_corewar(t_corewar *corewar)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < corewar->players_count)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			corewar->players[i].id,
			corewar->players[i].size,
			corewar->players[i].name,
			corewar->players[i].comment);
		i++;
	}
}

void		print_winner(t_corewar *corewar)
{
	int		player;
	char	*name;

	player = corewar->last_live_player;
	name = corewar->players[player - 1].name;
	if (corewar->processes_number == 0)
		ft_printf("Contestant %d, \"%s\", has won !\n", player, name);
}
