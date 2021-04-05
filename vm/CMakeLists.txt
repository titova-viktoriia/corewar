cmake_minimum_required(VERSION 3.17)
project(corewar C)

set(CMAKE_C_STANDARD 99)

find_library(libftprintf /libftprintf)
find_path (libftprintf libftprintf/includes libftprintf/srcs libftprintf/srcs/libft libftprintf/srcs/libft/includes operations)

include_directories(libftprintf libftprintf/includes libftprintf/srcs libftprintf/srcs/libft libftprintf/srcs/libft/includes operations)
link_directories(libftprintf)

add_executable(corewar
        includes/op.h
        includes/corewar.h
        #headers

        src/main_corewar.c
        src/live.c
        src/initialization.c
        src/ld.c
        src/add.c
        src/st.c
        src/sub.c
        src/and.c
        src/or.c
        src/xor.c
        src/zjmp.c
        src/ldi.c
        src/sti.c
        src/fork.c
        src/lld.c
        src/lldi.c
        src/lfork.c
        src/aff.c
        src/execution.c
        src/check_operations.c
        src/check_processes.c
        src/print.c
        src/args_validation.c
        src/help_functions.c
        src/help_operations_2.c
        src/help_operations.c
        src/process_initialization.c
        src/proccess_operations.c
        src/players_validation.c
        src/player_vaidation_2.c
        src/terminate.c
        src/arena_initialization.c

        #lib
        ./libftprintf/srcs/ft_count_of_digits.c
        ./libftprintf/srcs/ft_count_of_digits_llu.c
        ./libftprintf/srcs/ft_itoa_from_10_to_16.c
        ./libftprintf/srcs/ft_printf_e.c
        ./libftprintf/srcs/ft_printf.c
        ./libftprintf/srcs/ft_printf_b.c
        ./libftprintf/srcs/ft_printf_c.c
        ./libftprintf/srcs/ft_printf_d.c
        ./libftprintf/srcs/ft_printf_f.c
        ./libftprintf/srcs/ft_printf_o.c
        ./libftprintf/srcs/ft_printf_p.c
        ./libftprintf/srcs/ft_printf_percent.c
        ./libftprintf/srcs/ft_printf_s.c
        ./libftprintf/srcs/ft_printf_u.c
        ./libftprintf/srcs/ft_printf_x.c
        ./libftprintf/srcs/ft_putchar_with_counter.c
        ./libftprintf/srcs/ft_putstr_with_counter.c
        ./libftprintf/srcs/itobufferdata.c
        ./libftprintf/srcs/itobufferdata_llu.c
        ./libftprintf/srcs/parse_and_print.c
        ./libftprintf/srcs/print_common.c
        ./libftprintf/srcs/print_in_while.c
        ./libftprintf/srcs/print_pole_and_bufferdata.c
        ./libftprintf/srcs/get_parametr_pole.c
        ./libftprintf/srcs/fill_a_string_with_char.c
        ./libftprintf/srcs/get_float_number.c
        ./libftprintf/srcs/ft_printf_f_and_e_with_flags.c
        ./libftprintf/srcs/find_symbol.c
        ./libftprintf/srcs/count_of_second_part_for_float.c
        ./libftprintf/srcs/ft_printf_mas_i.c
        ./libftprintf/srcs/ft_printf_mas_c.c
        ./libftprintf/srcs/ft_new_arr_c.c
        ./libftprintf/srcs/ft_new_arr_i.c
        ./libftprintf/srcs/libft/ft_atoi.c
        ./libftprintf/srcs/libft/ft_atoi.c
        ./libftprintf/srcs/libft/ft_bzero.c
        ./libftprintf/srcs/libft/ft_isalnum.c
        ./libftprintf/srcs/libft/ft_isalpha.c
        ./libftprintf/srcs/libft/ft_isascii.c
        ./libftprintf/srcs/libft/ft_isdigit.c
        ./libftprintf/srcs/libft/ft_isprint.c
        ./libftprintf/srcs/libft/ft_itoa.c
        ./libftprintf/srcs/libft/ft_lstadd.c
        ./libftprintf/srcs/libft/ft_lstdel.c
        ./libftprintf/srcs/libft/ft_lstdelone.c
        ./libftprintf/srcs/libft/ft_lstiter.c
        ./libftprintf/srcs/libft/ft_lstmap.c
        ./libftprintf/srcs/libft/ft_lstnew.c
        ./libftprintf/srcs/libft/ft_memalloc.c
        ./libftprintf/srcs/libft/ft_memccpy.c
        ./libftprintf/srcs/libft/ft_memchr.c
        ./libftprintf/srcs/libft/ft_memcmp.c
        ./libftprintf/srcs/libft/ft_memcpy.c
        ./libftprintf/srcs/libft/ft_memdel.c
        ./libftprintf/srcs/libft/ft_memmove.c
        ./libftprintf/srcs/libft/ft_memset.c
        ./libftprintf/srcs/libft/ft_putchar.c
        ./libftprintf/srcs/libft/ft_putchar_fd.c
        ./libftprintf/srcs/libft/ft_putendl.c
        ./libftprintf/srcs/libft/ft_putendl_fd.c
        ./libftprintf/srcs/libft/ft_putnbr.c
        ./libftprintf/srcs/libft/ft_putnbr_fd.c
        ./libftprintf/srcs/libft/ft_putstr.c
        ./libftprintf/srcs/libft/ft_putstr_fd.c
        ./libftprintf/srcs/libft/ft_strcat.c
        ./libftprintf/srcs/libft/ft_strchr.c
        ./libftprintf/srcs/libft/ft_strclr.c
        ./libftprintf/srcs/libft/ft_strcmp.c
        ./libftprintf/srcs/libft/ft_strcpy.c
        ./libftprintf/srcs/libft/ft_strdel.c
        ./libftprintf/srcs/libft/ft_strdup.c
        ./libftprintf/srcs/libft/ft_strequ.c
        ./libftprintf/srcs/libft/ft_striter.c
        ./libftprintf/srcs/libft/ft_striteri.c
        ./libftprintf/srcs/libft/ft_strjoin.c
        ./libftprintf/srcs/libft/ft_strlcat.c
        ./libftprintf/srcs/libft/ft_strlen.c
        ./libftprintf/srcs/libft/ft_strmap.c
        ./libftprintf/srcs/libft/ft_strmapi.c
        ./libftprintf/srcs/libft/ft_strncat.c
        ./libftprintf/srcs/libft/ft_strncmp.c
        ./libftprintf/srcs/libft/ft_strncpy.c
        ./libftprintf/srcs/libft/ft_strnequ.c
        ./libftprintf/srcs/libft/ft_strnew.c
        ./libftprintf/srcs/libft/ft_strnstr.c
        ./libftprintf/srcs/libft/ft_strrchr.c
        ./libftprintf/srcs/libft/ft_strsplit.c
        ./libftprintf/srcs/libft/ft_strstr.c
        ./libftprintf/srcs/libft/ft_strsub.c
        ./libftprintf/srcs/libft/ft_strtrim.c
        ./libftprintf/srcs/libft/ft_tolower.c
        ./libftprintf/srcs/libft/ft_toupper.c
        ./libftprintf/srcs/libft/get_next_line.c
        ./libftprintf/srcs/libft/ft_iswhite.c
        ./libftprintf/srcs/libft/ft_lstadd_end.c
        ./libftprintf/srcs/libft/ft_atoi_long_long.c

        )

target_link_libraries(corewar libftprintf.a)