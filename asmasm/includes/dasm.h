/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:18:50 by ligeorgi          #+#    #+#             */
/*   Updated: 2021/03/27 09:07:48 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H

# define DASM_H

# include "libft.h"
# include "op.h"
# include "asm_op.h"

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIR_LAB,
	INDIRECT,
	INDIR_LAB,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;

static char				*g_type[] = {
	"COMMAND",
	"STRING",
	"LABEL",
	"OPERATOR",
	"REGISTER",
	"DIRECT",
	"DIR_LAB",
	"INDIRECT",
	"INDIR_LAB",
	"SEPARATOR",
	"NEW_LINE",
	"END"
};

typedef struct			s_token
{
	char				*content;
	t_type				type;
	unsigned			row;
	unsigned			column;
	struct s_token		*next;
}						t_token;

typedef struct			s_lab_pos
{
	unsigned			row;
	unsigned			column;
	int32_t				pos;
	int32_t				op_pos;
	size_t				size;
	struct s_lab_pos	*next;
}						t_lab_pos;

typedef struct			s_label
{
	char				*name;
	int32_t				op_pos;
	t_lab_pos			*lab_sublist;
	struct s_label		*next;
}						t_label;

typedef struct			s_data
{
	int					fd;
	unsigned			row;
	unsigned			column;
	char				*name;
	char				*comment;
	char				*code;
	int32_t				code_size;
	int32_t				pos;
	int32_t				op_pos;
	t_token				*tokens;
	t_label				*labels;
	t_token				*token;
}						t_data;

void					data_fill(t_data *data);
void					add_token(t_data *data, t_token *new);
void					data_print(t_data *data);
void					ft_throw(char *s);
void					get_name_and_comment(t_data *data);
void					get_code(t_data *data);
int8_t					get_args_types(t_data *data, t_op *op);
void					get_numbers_bytecode(t_data *data, t_op *op);

void					print_error(t_data *data);
void					wrong_token(t_token *token);
void					wrong_label(t_label *label);

void					get_bytecode(char *data, int32_t pos, int32_t value,
																size_t size);

void					add_label(t_label **list, t_label *new);
void					add_lab_pos(t_lab_pos **list, t_lab_pos *new);
t_label					*find_label(t_label *list, char *name);

t_token					*new_token(t_data *data, t_type type);
t_label					*new_label(char *name, int op_pos);
t_lab_pos				*new_lab_pos(t_data *data, t_token *token,
																size_t size);
int						get_line(int fd, char **row);
void					trim(t_data *data, const char *row);
char					*get_content(t_data *data, const char *row,
															unsigned start);
char					*concat(char **str1, char **str2);
void					get_new_row_and_column(t_data *data, const char *row);
t_bool					is_separator(int c);
t_bool					is_register(const char *arg);

#endif
