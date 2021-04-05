/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:25:49 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/25 08:06:52 by ligeorgi         ###   ########.fr       */
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

	name = ft_strsub(filename, 0, ft_strlen(filename) - 1);
	if (!name)
		ft_throw("ERROR: ft_strsub in main.c");
	if (!(filename = ft_strjoin(name, "cor")))
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
	data->row = 0;
	data->column = 0;
	data->op_pos = 0;
	data->labels = NULL;
	data->tokens = NULL;
	data->token = NULL;
}

static void			free_labels(t_data *data)
{
	t_label		*current;
	t_label		*tmp;
	t_lab_pos	*cur;
	t_lab_pos	*del;

	current = data->labels;
	while (current)
	{
		tmp = current;
		current = current->next;
		ft_strdel(&tmp->name);
		cur = tmp->lab_sublist;
		while (cur)
		{
			del = cur;
			cur = cur->next;
			ft_memdel((void **)&del);
		}
		ft_memdel((void **)&tmp);
	}
}

static void			data_free(t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	ft_strdel(&data->name);
	ft_strdel(&data->comment);
	ft_strdel(&data->code);
	free_labels(data);
	current = data->tokens;
	while (current)
	{
		tmp = current;
		current = current->next;
		ft_strdel(&tmp->content);
		ft_memdel((void **)&tmp);
	}
}

int					main(int argc, char **argv)
{
	t_data	data[1];
	char	*name;

	errno = 0;
	if (argc == 2 && ft_strlen(argv[1]) >= 2
			&& !ft_strcmp(ft_strchr(argv[1], '\0') - 2, ".s"))
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
		ft_printf("SUCCESS: \033[0;32m%s\033[0m assembled"
				" and saved as \033[0;32m%s\033[0m\n", argv[1], name);
		ft_strdel(&name);
		data_free(data);
	}
	else
		ft_printf("Usage: ./asm champion_name.s\n");
	return (0);
}
