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

int			main(int argc, char **argv)
{
	t_corewar	*corewar;

	if (argc > 1)
	{
		corewar = corewar_initialization();
		parse_and_validate_args(argc, argv, corewar, 1);
		validate_players(corewar);
		arena_initialization(corewar);
		process_initialization(corewar);
		hello_corewar(corewar);
		execution(corewar);
		print_winner(corewar);
		clean_corewar(corewar);
	}
	else
		print_rules();
	return (0);
}
