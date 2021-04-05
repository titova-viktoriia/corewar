/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:32:44 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/27 09:04:05 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

char			*concat(char **str1, char **str2)
{
	char *result;

	if (!(result = ft_strjoin(*str1, *str2)))
		ft_throw("ERROR: Can not init string");
	ft_strdel(str1);
	ft_strdel(str2);
	return (result);
}

void			get_new_row_and_column(t_data *data, const char *row)
{
	unsigned i;

	i = ++(data->column);
	while (row[i] && row[i] != '\"')
	{
		if (row[i] == '\n')
		{
			data->row++;
			data->column = 0;
		}
		else
			data->column++;
		i++;
	}
}

static int		new_str(char **str, char **row)
{
	char	*new;
	char	*div;

	div = *str ? ft_strchr(*str, '\n') : NULL;
	div++;
	if (!(*row = ft_strsub(*str, 0, div - *str)))
		return (-1);
	if (!ft_strlen(div))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(div);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

int				get_line(const int fd, char **row)
{
	static char		*str = NULL;
	char			buff[2048 + 1];
	ssize_t			size;
	char			*tmp;

	if (fd < 0 || !row || read(fd, buff, 0) < 0)
		return (-1);
	while (!(str ? ft_strchr(str, '\n') : NULL))
	{
		if (!(size = read(fd, buff, 2048)))
		{
			if (!(*row = str))
				return (0);
			str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		if (!str)
			return (-1);
	}
	return (new_str(&str, row));
}

void			data_print(t_data *data)
{
	int32_t	len;
	int32_t	pos;
	char	*bytecode;

	pos = 0;
	len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + data->pos;
	if (!(bytecode = ft_strnew((size_t)len)))
		ft_throw("ERROR: Can not initialize bytecode string");
	get_bytecode(bytecode, pos, COREWAR_EXEC_MAGIC, 4);
	pos += 4;
	ft_memcpy(&bytecode[pos], data->name, ft_strlen(data->name));
	pos += PROG_NAME_LENGTH + 4;
	get_bytecode(bytecode, pos, data->pos, 4);
	pos += 4;
	ft_memcpy(&bytecode[pos], data->comment, ft_strlen(data->comment));
	pos += COMMENT_LENGTH + 4;
	ft_memcpy(&bytecode[pos], data->code, (size_t)data->pos);
	write(data->fd, bytecode, (size_t)len);
	free(bytecode);
}
