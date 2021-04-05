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

#include <stdio.h>
#include "../includes/corewar.h"

void	clean_players(t_corewar *corewar)
{
	int		i;

	i = 0;
	while (i < corewar->players_init_count)
	{
		if (corewar->players[i].name)
			free(corewar->players[i].name);
		if (corewar->players[i].code)
			free(corewar->players[i].code);
		if (corewar->players[i].comment)
			free(corewar->players[i].comment);
		i++;
	}
}

void	clean_corewar(t_corewar *corewar)
{
	t_process	*help;

	if (corewar->processes != NULL)
	{
		while (corewar->processes)
		{
			help = corewar->processes->next;
			free(corewar->processes);
			corewar->processes = help;
		}
	}
	clean_players(corewar);
	free(corewar);
}

void	terminate(t_corewar *corewar, char *message)
{
	clean_corewar(corewar);
	perror(message);
	exit(0);
}
