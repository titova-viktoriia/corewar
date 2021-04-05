COREWAR = corewar

#sources and objects
SRC =	add.c \
        check_operations.c \
        help_operations_2.c \
        lfork.c \
        main_corewar.c \
        proccess_operations.c \
        terminate.c \
        aff.c \
        check_processes.c \
        help_operations.c \
        or.c \
        process_initialization.c \
        xor.c \
        and.c \
        execution.c \
        initialization.c \
        live.c \
        players_validation.c \
        st.c \
        zjmp.c \
        arena_initialization.c \
        fork.c \
        ld.c \
        lld.c \
        player_vaidation_2.c \
        sti.c \
        args_validation.c \
        help_functions.c\
        ldi.c \
        lldi.c \
        print.c \
        sub.c

SRC_PATH = $(addprefix $(SRCDIR), $(SRC))
OBJ = $(addprefix $(OBJDIR), $(SRC:%.c=%.o))

#directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR  = ./obj_corewar/

#includes
INC = -I ./includes

#flags
FLAGS = -Wall -Wextra -Werror -Wno-unused-variable

#library
FT		= ./libftprintf/
FT_LIB	= $(addprefix $(FT),libftprintf.a)
FT_INC	= -I ./libftprintf/includes -I ./corewar/libftprintf/srcs/libft/includes/
FT_LNK	= ./libftprintf/libftprintf.a

all: obj $(FT_LIB) $(COREWAR)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	gcc $(FLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(COREWAR): $(OBJ)
	gcc $(OBJ) $(FT_LNK) -o $(COREWAR)

$(FT_LIB):
	make -C $(FT)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean

fclean: clean
	rm -rf $(COREWAR)
	make -C $(FT) fclean

re: fclean all