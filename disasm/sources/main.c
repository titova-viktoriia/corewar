/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:25:49 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:29:53 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include <errno.h>
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

static char			*new_name(char *filename)
{
	char	*name;

	name = ft_strsub(filename, 0, ft_strlen(filename) - 4);
	if (!name)
		ft_throw("ERROR: ft_strsub in main.c");
	if (!(filename = ft_strjoin(name, "_dis.s")))
		ft_throw("ERROR: ft_strjoin in main.c");
	ft_strdel(&name);
	return (filename);
}

static void			data_init(t_data *data)
{
	data->name = NULL;
	data->comment = NULL;
	data->code_size = 0;
	data->code = NULL;
	data->pos = 0;
	data->instructions = NULL;
}

static void			data_free(t_data *data)
{
	t_instruction	*current;
	t_instruction	*tmp;

	ft_strdel(&data->name);
	ft_strdel(&data->comment);
	ft_memdel((void **)&data->code);
	current = data->instructions;
	while (current)
	{
		tmp = current;
		current = current->next;
		ft_memdel((void **)&tmp);
	}
}

int					main(int argc, char **argv)
{
	t_data	data[1];
	char	*name;

	errno = 0;
	if (argc == 2 && ft_strlen(argv[1]) >= 4
			&& !ft_strcmp(ft_strchr(argv[1], '\0') - 4, ".cor"))
	{
		if ((data->fd = open(argv[1], O_RDONLY)) == -1)
			ft_throw("ERROR: Can not open file in main.c");
		data_init(data);
		data_fill(data);
		close(data->fd);
		name = new_name(argv[1]);
		if ((data->fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
			ft_throw("ERROR: Can not create file in main.c");
		data_print(data);
		close(data->fd);
		ft_printf("SUCCESS: \033[0;32m%s\033[0m disassembled"
				" and saved as \033[0;32m%s\033[0m\n", argv[1], name);
		ft_strdel(&name);
		data_free(data);
	}
	else
		ft_printf("Usage: ./dasm champion_name.cor\n");
	return (0);
}
