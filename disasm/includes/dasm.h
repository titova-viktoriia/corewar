/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:18:50 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/23 09:31:47 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H

# define DASM_H

# include "libft.h"
# include "op.h"
# include "asm_op.h"

typedef struct			s_instruction
{
	t_op					*op;
	uint8_t					args_types[3];
	int32_t					args[3];
	struct s_instruction	*next;
}						t_instruction;

typedef struct			s_data
{
	int					fd;
	char				*name;
	char				*comment;
	int32_t				code_size;
	uint8_t				*code;
	int32_t				pos;
	t_instruction		*instructions;
}						t_data;

void					data_fill(t_data *data);
void					data_print(t_data *data);
t_instruction			*get_instruction(t_data *data);
int						get_args_types(t_data *data,
												t_instruction *instruction);
int32_t					get_int(const uint8_t *code, size_t size);
void					print_warning(size_t pos, size_t len);
void					print_error(t_data *data, char *err);
void					ft_throw(char *s);

#endif
