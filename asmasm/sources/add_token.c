/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 06:53:48 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/27 09:06:00 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

t_bool			is_separator(int c)
{
	return (c == '\0' || c == '.' || c == '\"' || ft_isspace(c)
			|| c == DIRECT_CHAR || c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR || c == ALT_COMMENT_CHAR);
}

t_bool			is_register(const char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) >= 2 && ft_strlen(arg) <= 3 && arg[i] == 'r')
	{
		i++;
		while (ft_isdigit(arg[i]))
			i++;
		return (!arg[i] && ft_atoi(&arg[1]) > 0);
	}
	return (false);
}

t_token			*new_token(t_data *data, t_type type)
{
	t_token	*token;

	if (!(token = (t_token *)ft_memalloc(sizeof(t_token))))
		ft_throw("ERROR: Can not init token");
	token->content = NULL;
	token->type = type;
	token->row = data->row;
	token->column = data->column;
	if (type == SEPARATOR || type == NEW_LINE)
		token->column--;
	token->next = NULL;
	return (token);
}

void			add_token(t_data *data, t_token *new)
{
	if (data->token)
	{
		if (data->token->type == NEW_LINE && new->type == NEW_LINE)
			ft_memdel((void **)&new);
		else
		{
			data->token->next = new;
			data->token = new;
		}
	}
	else
	{
		if (new->type == NEW_LINE)
			ft_memdel((void **)&new);
		else
		{
			data->token = new;
			data->tokens = new;
		}
	}
}
