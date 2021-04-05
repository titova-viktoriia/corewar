# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/10 09:12:01 by ligeorgi          #+#    #+#              #
#    Updated: 2020/12/10 09:12:15 by ligeorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_A = asm
NAME_D = dasm
NAME_C = corewar

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBRARIES = -lft -L$(LIBFT_DIRECTORY)
A_INCLUDES = -I$(A_HEADERS_DIRECTORY) -I$(LIBFT_HEADERS_DIR)
D_INCLUDES = -I$(D_HEADERS_DIRECTORY) -I$(LIBFT_HEADERS_DIR)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS_DIR = $(LIBFT_DIRECTORY)includes/

A_HEADERS_LIST = \
	op.h\
	asm_op.h\
	dasm.h

A_HEADERS_DIRECTORY = ./asmasm/includes/
A_HEADERS = $(addprefix $(A_HEADERS_DIRECTORY), $(A_HEADERS_LIST))

A_SOURCES_DIRECTORY = ./asmasm/sources/
A_SOURCES_LIST = \
	main.c\
	data_fill.c\
	get_code.c\
	get_name_and_comment.c\
	add_token.c\
	get_args_types.c\
	get_args_types_2.c\
	data_print.c\
	messages.c\
	utils.c

A_SOURCES = $(addprefix $(A_SOURCES_DIRECTORY), $(A_SOURCES_LIST))

A_OBJECTS_DIRECTORY = ./asmasm/objects/
A_OBJECTS_LIST = $(patsubst %.c, %.o, $(A_SOURCES_LIST))
A_OBJECTS = $(addprefix $(A_OBJECTS_DIRECTORY), $(A_OBJECTS_LIST))

D_HEADERS_LIST = \
	op.h\
	asm_op.h\
	dasm.h

D_HEADERS_DIRECTORY = ./disasm/includes/
D_HEADERS = $(addprefix $(D_HEADERS_DIRECTORY), $(D_HEADERS_LIST))

D_SOURCES_DIRECTORY = ./disasm/sources/
D_SOURCES_LIST = \
	main.c\
	data_fill.c\
	get_instruction.c\
	get_args_types.c\
	data_print.c\
	messages.c\
	utils.c

D_SOURCES = $(addprefix $(D_SOURCES_DIRECTORY), $(D_SOURCES_LIST))

D_OBJECTS_DIRECTORY = ./disasm/objects/
D_OBJECTS_LIST = $(patsubst %.c, %.o, $(D_SOURCES_LIST))
D_OBJECTS = $(addprefix $(D_OBJECTS_DIRECTORY), $(D_OBJECTS_LIST))

COREWAR_DIRECTORY = ./vm/
COREWAR_EXEC = $(addprefix $(COREWAR_DIRECTORY), $(NAME_C))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

include $(LIBFT_DIRECTORY)libft.mk

LIBFT_1 = $(subst ./, , $(LIBFT_HEADERS))
LIBFT_1 += $(subst ./, , $(LIBFT_SOURCES))
LIBFT_2 = $(addprefix $(LIBFT_DIRECTORY), $(LIBFT_1))

all: $(NAME_C) $(NAME_A) $(NAME_D)

$(NAME_A): $(LIBFT) $(A_OBJECTS_DIRECTORY) $(A_OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(A_INCLUDES) $(A_OBJECTS) -o $(NAME_A)
	@echo "$(NAME_A): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME_A): $(GREEN)$(NAME_A) was created$(RESET)"

$(NAME_D): $(LIBFT) $(D_OBJECTS_DIRECTORY) $(D_OBJECTS)
	@$(CC) $(FLAGS) $(LIBRARIES) $(D_INCLUDES) $(D_OBJECTS) -o $(NAME_D)
	@echo "$(NAME_D): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME_D): $(GREEN)$(NAME_D) was created$(RESET)"

$(A_OBJECTS_DIRECTORY):
	@mkdir -p $(A_OBJECTS_DIRECTORY)
	@echo "$(NAME_A): $(GREEN)$(A_OBJECTS_DIRECTORY) was created$(RESET)"

$(A_OBJECTS_DIRECTORY)%.o : $(A_SOURCES_DIRECTORY)%.c $(A_HEADERS) $(LIBFT)
	@$(CC) $(FLAGS) -c $(A_INCLUDES) $< -o $@

$(D_OBJECTS_DIRECTORY):
	@mkdir -p $(D_OBJECTS_DIRECTORY)
	@echo "$(NAME_D): $(GREEN)$(D_OBJECTS_DIRECTORY) was created$(RESET)"

$(D_OBJECTS_DIRECTORY)%.o : $(D_SOURCES_DIRECTORY)%.c $(D_HEADERS) $(LIBFT)
	@$(CC) $(FLAGS) -c $(D_INCLUDES) $< -o $@

$(LIBFT): $(LIBFT_2)
	@echo "$(NAME_A): $(GREEN)Creating $(LIBFT)$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(NAME_C):
	@$(MAKE) -sC $(COREWAR_DIRECTORY)
	@mv $(COREWAR_EXEC) ./
	@echo "$(NAME_C): $(GREEN)$(NAME_C) was created$(RESET)"

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(A_OBJECTS_DIRECTORY)
	@echo "$(NAME_A): $(RED)$(A_OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME_A): $(RED)object files were deleted$(RESET)"
	@rm -rf $(D_OBJECTS_DIRECTORY)
	@echo "$(NAME_D): $(RED)$(D_OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME_D): $(RED)object files were deleted$(RESET)"
	@$(MAKE) -sC $(COREWAR_DIRECTORY) clean
	@echo "$(NAME_C): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(LIBFT): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME_A)
	@echo "$(NAME_A): $(RED)$(NAME_A) was deleted$(RESET)"
	@rm -f $(NAME_D)
	@echo "$(NAME_D): $(RED)$(NAME_D) was deleted$(RESET)"
	@rm -f $(NAME_C)
	@echo "$(NAME_C): $(RED)$(NAME_C) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
