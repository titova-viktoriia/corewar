
NAME = libftprintf.a

LIBFT_A =	libft.a

COMP =		gcc -Wall -Werror -Wextra $(PRINTF_H) $(LIBFT_H) -c -o

PRINTF_H =	-I includes/
LIBFT_H = 	-I srcs/libft/includes

OBJ_DIR =	obj/
SRC_DIR =	srcs/
LIB_DIR =	srcs/libft/

CFILE =		ft_count_of_digits.c \
            ft_count_of_digits_llu.c \
            ft_itoa_from_10_to_16.c \
            ft_printf_e.c \
            ft_printf.c \
            ft_printf_b.c \
            ft_printf_c.c \
            ft_printf_d.c \
            ft_printf_f.c \
            ft_printf_o.c \
            ft_printf_p.c \
            ft_printf_percent.c \
            ft_printf_s.c \
            ft_printf_u.c \
            ft_printf_x.c \
            ft_putchar_with_counter.c \
            ft_putstr_with_counter.c \
            itobufferdata.c \
            itobufferdata_llu.c \
            parse_and_print.c \
            print_common.c \
            print_in_while.c \
            print_pole_and_bufferdata.c \
            get_parametr_pole.c \
            fill_a_string_with_char.c \
            get_float_number.c \
            ft_printf_f_and_e_with_flags.c \
            find_symbol.c \
            count_of_second_part_for_float.c \
            ft_printf_mas_i.c \
            ft_printf_mas_c.c \
            ft_new_arr_c.c \
            ft_new_arr_i.c

CFIND =		$(CFILE:%=$(SRC_DIR)%)

OFILE =		$(CFILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(OFILE))

all: $(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		@echo Create: ft_printf Object directory

$(NAME): $(OBJ_DIR) $(OBJ)
		@echo LIBFT START
		@make -C $(LIB_DIR)
		@echo Copying $(LIBFT_A) to root.
		@cp $(LIB_DIR)$(LIBFT_A) .
		@mv $(LIBFT_A) $(NAME)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)
		@echo Merged: $(NAME) with $(LIBFT_A)
		@echo FT_PRINTF COMPLETE

$(OBJ): $(CFIND)
		@$(MAKE) $(OFILE)

$(OFILE):
		@echo Create: $(@:obj/%=%)
		@$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
		@rm -rf $(OBJ_DIR)
		@make -C $(LIB_DIR) clean
		@echo Cleaned ft_printf object files

fclean: clean
		@rm -f $(NAME)
		@make -C $(LIB_DIR) fclean
		@echo Cleaned $(NAME)

re: fclean all

.PHONY: all clean flcean re