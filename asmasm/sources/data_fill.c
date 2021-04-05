/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:33 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/27 09:02:47 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

static void				next_char(t_data *data, char *row,
		unsigned start, t_token *token)
{
	unsigned column;

	token->column = start;
	column = data->column;
	while (row[data->column]
			&& ft_strchr(LABEL_CHARS, row[data->column]))
		data->column++;
	if ((data->column - column) && row[data->column] == LABEL_CHAR
			&& ++data->column)
	{
		token->content = get_content(data, row, start);
		token->type = LABEL;
		add_token(data, token);
	}
	else if ((data->column - column) && is_separator(row[data->column]))
	{
		token->content = get_content(data, row, start);
		if (token->type == INDIRECT)
			token->type = (is_register(token->content)) ? REGISTER : OPERATOR;
		add_token(data, token);
	}
	else
		print_error(data);
}

static void				next_digit(t_data *data, char *row,
		unsigned start, t_token *token)
{
	unsigned column;

	token->column = start;
	if (row[data->column] == '-')
		data->column++;
	column = data->column;
	while (ft_isdigit(row[data->column]))
		data->column++;
	if ((data->column - column)
			&& (token->type == DIRECT || is_separator(row[data->column])))
	{
		token->content = get_content(data, row, start);
		add_token(data, token);
	}
	else if (token->type != DIRECT)
	{
		data->column = start;
		next_char(data, row, start, token);
	}
	else
		print_error(data);
}

static void				next_string(t_data *data, char **row,
		unsigned start, t_token *token)
{
	char	*end;
	ssize_t	size;
	char	*str;
	char	*new;

	token->column = start;
	size = 1;
	while (!(end = ft_strchr(&((*row)[start + 1]), '\"'))
			&& (size = get_line(data->fd, &str)) > 0)
		*row = concat(row, &str);
	get_new_row_and_column(data, *row);
	(size == -1) ? ft_throw("ERROR: Can not read line in next_string()") : 0;
	(size == 0) ? print_error(data) : 0;
	if (!(token->content = ft_strsub(*row, start, end + 1 - &((*row)[start]))))
		ft_throw("ERROR: Can not init string in next_string()");
	if (end - data->column != *row)
	{
		if (!(new = ft_strdup(end - data->column)))
			ft_throw("ERROR: Can not init string in next_string()");
		ft_strdel(row);
		*row = new;
	}
	data->column++;
	add_token(data, token);
}

static void				get_token(t_data *data, char c, char **row)
{
	if (c == '.')
		next_char(data, *row, data->column++, new_token(data, COMMAND));
	else if (c == LABEL_CHAR)
		next_char(data, *row, data->column++, new_token(data, INDIR_LAB));
	else if (c == DIRECT_CHAR && ++data->column)
	{
		if (*(*row + data->column) == LABEL_CHAR && ++data->column)
			next_char(data, *row, data->column - 2, new_token(data, DIR_LAB));
		else
			next_digit(data, *row, data->column - 1, new_token(data, DIRECT));
	}
	else if (c == SEPARATOR_CHAR && ++data->column)
		add_token(data, new_token(data, SEPARATOR));
	else if (c == '\n' && ++data->column)
		add_token(data, new_token(data, NEW_LINE));
	else if (c == '\"')
		next_string(data, row, data->column, new_token(data, STRING));
	else
		next_digit(data, *row, data->column, new_token(data, INDIRECT));
}

void					data_fill(t_data *data)
{
	ssize_t	size;
	char	*row;

	while (++data->row && !(data->column = 0)
			&& (size = get_line(data->fd, &row)) > 0)
	{
		while (row[data->column])
		{
			trim(data, row);
			if (row[data->column])
				get_token(data, row[data->column], &row);
		}
		ft_strdel(&row);
	}
	if (size == -1)
		ft_throw("ERROR: Can not read line in data_fill()");
	add_token(data, new_token(data, END));
	data->token = data->tokens;
	get_name_and_comment(data);
	get_code(data);
}
