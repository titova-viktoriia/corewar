/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:12:27 by hdeckard          #+#    #+#             */
/*   Updated: 2021/01/06 18:25:33 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/srcs/libft/includes/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <inttypes.h>

# define DIR_SIZE_4 4
# define DIR_SIZE_2 2

typedef struct	s_player
{
	int				id;
	char			*name;
	char			*comment;
	uint8_t			*code;
	int				size;
	int				current_lives_number;
	int				previous_lives_number;
	int				last_live;
}				t_player;

typedef struct	s_process
{
	int					uid;
	int					flag_carry;
	uint8_t				operations_code;
	int32_t				pc;
	int					cycle_before_execution;
	int					last_live_operation_cycle;
	int					pc_buffer;
	uint8_t				args[3];
	int32_t				registers[REG_NUMBER];
	int					args_validation;
	struct s_process	*next;
}				t_process;

typedef struct	s_corewar
{
	int			dump_flag;
	int			d_flag;
	int			live_flag;
	int			players_count;
	int			players_init_count;
	int			players_number_buffer[MAX_PLAYERS];
	char		*players_file_buffer[MAX_PLAYERS];
	uint8_t		arena[MEM_SIZE];
	t_player	players[MAX_PLAYERS];
	t_process	*processes;
	int			processes_number;
	int			last_live_player;
	int			cycles_to_die;
	int			total_cycles_number;
	int			operation_live_number;
	int			current_cycle;
	int			process_id_counter;
	int			die_check_counter;
	int			dump_cycles;
}				t_corewar;

typedef struct	s_op
{
	char		*operation_name;
	char		*operation_description;
	int			args_number;
	uint8_t		args_types[3];
	uint8_t		operation_code;
	int			cycles_before_execution;
	int			flag_carry;
	int			args_types_code;
	int			t_dir_size;
	void		(*function)(t_process *, t_corewar *);
}				t_op;

void			op_live(t_process *process, t_corewar *corewar);
void			op_ld(t_process *process, t_corewar *corewar);
void			op_st(t_process *process, t_corewar *corewar);
void			op_add(t_process *process, t_corewar *corewar);
void			op_sub(t_process *process, t_corewar *corewar);
void			op_and(t_process *process, t_corewar *corewar);
void			op_or(t_process *process, t_corewar *corewar);
void			op_xor(t_process *process, t_corewar *corewar);
void			op_zjmp(t_process *process, t_corewar *corewar);
void			op_ldi(t_process *process, t_corewar *corewar);
void			op_sti(t_process *process, t_corewar *corewar);
void			op_fork(t_process *process, t_corewar *corewar);
void			op_lld(t_process *process, t_corewar *corewar);
void			op_lldi(t_process *process, t_corewar *corewar);
void			op_lfork(t_process *process, t_corewar *corewar);
void			op_aff(t_process *process, t_corewar *corewar);

static struct s_op		g_ops[16] = {
	{
		.operation_name = "live",
		.operation_description = "alive",
		.operation_code = 0x01,
		.args_number = 1,
		.args_types_code = 0,
		.args_types = {T_DIR, 0, 0},
		.flag_carry = 0,
		.t_dir_size = 4,
		.cycles_before_execution = 10,
		.function = &op_live
	},
	{
		.operation_name = "ld",
		.operation_description = "load",
		.operation_code = 0x02,
		.args_number = 2,
		.args_types_code = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 5,
		.function = &op_ld
	},
	{
		.operation_name = "st",
		.operation_description = "store",
		.operation_code = 0x03,
		.args_number = 2,
		.args_types_code = 1,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.flag_carry = 0,
		.t_dir_size = 4,
		.cycles_before_execution = 5,
		.function = &op_st
	},
	{
		.operation_name = "add",
		.operation_description = "addition",
		.operation_code = 0x04,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 10,
		.function = &op_add
	},
	{
		.operation_name = "sub",
		.operation_description = "soustraction",
		.operation_code = 0x05,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG, T_REG, T_REG},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 10,
		.function = &op_sub
	},
	{
		.operation_name = "and",
		.operation_description = "et (and  r1, r2, r3   r1&r2 -> r3",
		.operation_code = 0x06,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 6,
		.function = &op_and
	},
	{
		.operation_name = "or",
		.operation_description = "ou  (or   r1, r2, r3   r1 | r2 -> r3",
		.operation_code = 0x07,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 6,
		.function = &op_or
	},
	{
		.operation_name = "xor",
		.operation_description = "ou (xor  r1, r2, r3   r1^r2 -> r3",
		.operation_code = 0x08,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 6,
		.function = &op_xor
	},
	{
		.operation_name = "zjmp",
		.operation_description = "jump if zero",
		.operation_code = 0x09,
		.args_number = 1,
		.args_types_code = 0,
		.args_types = {T_DIR, 0, 0},
		.flag_carry = 0,
		.t_dir_size = 2,
		.cycles_before_execution = 20,
		.function = &op_zjmp
	},
	{
		.operation_name = "ldi",
		.operation_description = "load index",
		.operation_code = 0x0A,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.flag_carry = 0,
		.t_dir_size = 2,
		.cycles_before_execution = 25,
		.function = &op_ldi
	},
	{
		.operation_name = "sti",
		.operation_description = "store index",
		.operation_code = 0x0B,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.flag_carry = 0,
		.t_dir_size = 2,
		.cycles_before_execution = 25,
		.function = &op_sti
	},
	{
		.operation_name = "fork",
		.operation_description = "fork",
		.operation_code = 0x0C,
		.args_number = 1,
		.args_types_code = 0,
		.args_types = {T_DIR, 0, 0},
		.flag_carry = 0,
		.t_dir_size = 2,
		.cycles_before_execution = 800,
		.function = &op_fork
	},
	{
		.operation_name = "lld",
		.operation_description = "long load",
		.operation_code = 0x0D,
		.args_number = 2,
		.args_types_code = 1,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.flag_carry = 1,
		.t_dir_size = 4,
		.cycles_before_execution = 10,
		.function = &op_lld
	},
	{
		.operation_name = "lldi",
		.operation_description = "long load index",
		.operation_code = 0x0E,
		.args_number = 3,
		.args_types_code = 1,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.flag_carry = 1,
		.t_dir_size = 2,
		.cycles_before_execution = 50,
		.function = &op_lldi
	},
	{
		.operation_name = "lfork",
		.operation_description = "alive",
		.operation_code = 0x0F,
		.args_number = 1,
		.args_types_code = 0,
		.args_types = {T_DIR, 0, 0},
		.flag_carry = 0,
		.t_dir_size = 2,
		.cycles_before_execution = 1000,
		.function = &op_lfork
	},
	{
		.operation_name = "aff",
		.operation_description = "alive",
		.operation_code = 0x10,
		.args_number = 1,
		.args_types_code = 1,
		.args_types = {T_REG, 0, 0},
		.flag_carry = 0,
		.t_dir_size = 4,
		.cycles_before_execution = 2,
		.function = &op_aff
	}
};

t_corewar		*corewar_initialization();
void			parse_and_validate_args(int argc,
								char **argv, t_corewar *corewar, int i);
void			validate_players(t_corewar *corewar);
void			terminate(t_corewar *corewar, char *message);
int				check_dublicates(int num, const int *nums);
void			arena_initialization(t_corewar *corewar);
void			process_initialization(t_corewar *corewar);
int8_t			get_one_byte(uint8_t *arena, int pc);
int32_t			get_t_ind_value(const uint8_t *arena, int current_pc, int pc);
int32_t			get_int32_from_arena(const uint8_t *arena, int pc, int size);
int				get_pc(int pc);
void			set_int32_t_value_on_arena(int32_t value,
							int32_t pc, t_corewar *corewar);
int32_t			get_value_from_register(t_corewar *corewar,
							t_process *process, int current_pc);
int				add_step(uint8_t argument, t_op	*operation);
int32_t			get_int32_t_argument(t_corewar *corewar,
							t_process *process, int arg_index, int current_pc);
int32_t			get_int32_t_argument_2(t_corewar *corewar,
							t_process *process, int arg_index, int current_pc);
void			copy_registers(t_process *new, t_process *parent);
t_process		*duplicate_process(t_process *parent, int uid,
							t_corewar *corewar);
t_process		*delete_process(int process_to_delete_uid,
							t_process *processes);
void			print_arena(t_corewar *corewar);
void			print_rules(void);
void			hello_corewar(t_corewar *corewar);
void			print_winner(t_corewar *corewar);
void			check_all_processes(t_corewar *corewar);
void			check_died_processes(t_corewar *corewar);
int				check_if_operation_exists(uint8_t operations_code);
void			check_arguments(t_process *process, t_corewar *corewar);
void			set_process_args_type(t_process *process, t_corewar *corewar);
void			check_process_args_type(t_process *process);
void			set_operation(t_process *process, t_corewar *corewar);
void			reset_process(t_process *process);
void			reduce_cycles_to_die(t_corewar *corewar);
void			reset_player_live(t_corewar *corewar);
void			execution(t_corewar *corewar);
int				ft_isnumber(char *str);
int				ft_strncmp_end(char *str, char *end);
int				get_type_code(int8_t argument_type);
int				find_number(int index, const int *nums, int size);
int32_t			get_t_ind_value_without_idx_mode(const uint8_t *arena,
													int current_pc, int pc);
void			update_players_numbers(t_corewar *corewar);
int				get_player_index_from_buffer(int index, const int *buffer);
void			init_player(t_player *player, int id);
int32_t			from_bytecode_to_int32(const uint8_t *bytecode, size_t size);
void			clean_corewar(t_corewar *corewar);

#endif
