/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 06:48:26 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/25 06:50:43 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"
#include "ft_printf.h"

void			trim(t_data *data, const char *row)
{
	while (row[data->column] == '\t' || row[data->column] == '\v' ||
			row[data->column] == '\f' || row[data->column] == '\r' ||
			row[data->column] == ' ')
		data->column++;
	if (row[data->column] == COMMENT_CHAR
			|| row[data->column] == ALT_COMMENT_CHAR)
		while (row[data->column] && row[data->column] != '\n')
			data->column++;
}

char			*get_content(t_data *data, const char *row, unsigned start)
{
	char	*content;

	if (!(content = ft_strsub(row, start, data->column - start)))
		ft_throw("ERROR: Can not init string in get_content()");
	return (content);
}

static void		get_name(t_data *data)
{
	if (data->token->type == STRING)
	{
		if (!(data->name = ft_strsub(data->token->content,
						1, ft_strlen(data->token->content) - 2)))
			ft_throw("ERROR: Can not init string in get_name()");
		if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		{
			ft_dprintf(2, "Champion name length > %u\n", PROG_NAME_LENGTH);
			exit(1);
		}
		data->token = data->token->next;
	}
	else
		wrong_token(data->token);
}

static void		get_comment(t_data *data)
{
	if (data->token->type == STRING)
	{
		if (!(data->comment = ft_strsub(data->token->content,
						1, ft_strlen(data->token->content) - 2)))
			ft_throw("ERROR: Can not init string in get_comment()");
		if (ft_strlen(data->comment) > COMMENT_LENGTH)
		{
			ft_dprintf(2, "Champion comment length > %u)\n",
					COMMENT_LENGTH);
			exit(1);
		}
		data->token = data->token->next;
	}
	else
		wrong_token(data->token);
}

void			get_name_and_comment(t_data *data)
{
	while (!data->name || !data->comment)
	{
		if (data->token->type == COMMAND && !data->name
				&& !ft_strcmp(data->token->content, NAME_CMD_STRING))
		{
			data->token = data->token->next;
			get_name(data);
			if (data->token->type != NEW_LINE)
				wrong_token(data->token);
		}
		else if (data->token->type == COMMAND && !data->comment
				&& !ft_strcmp(data->token->content, COMMENT_CMD_STRING))
		{
			data->token = data->token->next;
			get_comment(data);
			if (data->token->type != NEW_LINE)
				wrong_token(data->token);
		}
		else
			wrong_token(data->token);
		data->token = data->token->next;
	}
}
