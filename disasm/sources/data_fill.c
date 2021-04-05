/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:33 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:32:22 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include <fcntl.h>
#include <unistd.h>

static void			add_instruction(t_data *data, t_instruction *new)
{
	t_instruction *current;

	current = data->instructions;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		data->instructions = new;
}

static int32_t		read_four_bytes(int fd)
{
	ssize_t	size;
	uint8_t	buffer[4];

	size = read(fd, buffer, 4);
	if (size == -1)
		ft_throw("ERROR: Can not read file with champion");
	if (size < 4)
		ft_throw("ERROR: Invalid file with champion");
	return (get_int(buffer, 4));
}

static char			*read_string(int fd, size_t len)
{
	ssize_t		size;
	char		*buffer;
	size_t		i;

	if (!(buffer = ft_strnew(len)))
		ft_throw("ERROR: Can not initialize string");
	size = read(fd, buffer, len);
	if (size == -1)
		ft_throw("ERROR: Can not read file with champion");
	if (size < (ssize_t)len)
		ft_throw("ERROR: Invalid file with champion");
	i = ft_strlen(buffer);
	while (i < len)
	{
		if (buffer[i])
		{
			print_warning(i, len);
			break ;
		}
		i++;
	}
	return (buffer);
}

static uint8_t		*read_code(int fd, size_t len)
{
	ssize_t	size;
	uint8_t	*buffer;
	uint8_t	byte;

	if (!(buffer = ft_memalloc(len)))
		ft_throw("ERROR: Can not initialize string of code");
	size = read(fd, buffer, len);
	if (size == -1)
		ft_throw("ERROR: Can not read file with champion");
	if (size < (ssize_t)len || read(fd, &byte, 1) != 0)
		ft_throw("ERROR: Invalid file with champion");
	return (buffer);
}

void				data_fill(t_data *data)
{
	if (read_four_bytes(data->fd) != COREWAR_EXEC_MAGIC)
		ft_throw("ERROR: Invalid magic header");
	data->name = read_string(data->fd, PROG_NAME_LENGTH);
	if (read_four_bytes(data->fd) != 0)
		ft_throw("ERROR: No null control bytes");
	if ((data->code_size = read_four_bytes(data->fd)) < 0)
		ft_throw("ERROR: Invalid code size");
	data->comment = read_string(data->fd, COMMENT_LENGTH);
	if (read_four_bytes(data->fd) != 0)
		ft_throw("ERROR: No null control bytes");
	data->code = read_code(data->fd, (size_t)data->code_size);
	while (data->pos < data->code_size)
		add_instruction(data, get_instruction(data));
}
