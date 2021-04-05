/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_eE.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:20 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/05 17:30:29 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FT_PRINTF_H
# define PRINTF_FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <ctype.h>
# include <unistd.h>
# include "../srcs/libft/includes/libft.h"
# include <stdio.h>
# define CHARS "0123456789 +-.#*lhL"
# define SPEC_TYPE "%cspdiouxXfeEbCI"
# define WHITE "\e[030m"
# define RED "\e[031m"
# define SALAT "\e[032m"
# define YELLOW "\e[033m"
# define BLUE "\e[034m"
# define SIREN "\e[035m"
# define AQUA "\e[036m"
# define GRAY "\e[037m"
# define W_FON "\e[040m"
# define ENDC "\e[0m"

typedef struct	s_data
{
	va_list			args;
	unsigned int	len;
	unsigned int	index;
	int				flag_minus;
	int				flag_plus;
	int				flag_hash;
	int				flag_space;
	int				fl_ppole_long;
	int				fl_ppole_int;
	int				fl_0pole_long;
	int				fl_znak_int;
	char			fl_znak;
	int				fl_0faktor;
	int				flag_zero;
	size_t			width;
	int				precision;
	int				flag_l;
	int				flag_large_l;
	int				flag_h;
	int				flag_dot;
	char			type;
	char			*bufferdata;
}				t_data;

int				ft_printf(const char *format, ...);
void			parse_and_print(t_data *data, const char *format);
int				count_of_digits_16(unsigned long int n);
char			*ft_itoa_from_10_to_16(unsigned long int n, t_data *data);
void			ft_putchar_with_counter(char c, t_data *data);
void			ft_putstr_with_counter(char *str, t_data *data);
void			print_in_while(char c, int count, t_data *data);
void			install_data(t_data *data);
void			print_common(t_data *data);
void			ft_printf_percent(t_data *data);
void			ft_printf_c(t_data *data);
void			ft_printf_s(t_data *data);
void			ft_printf_p(t_data *data);
void			ft_printf_f(t_data *data);
void			ft_printf_xx(t_data *data);
int				count_of_second_part(t_data *data);
void			get_float_str(long double b, t_data *data);
void			ft_printf_fe_flags(long double nb, int len, t_data *data);
void			ft_printf_e(t_data *data);
void			ft_printf_d(t_data *data);
void			itobufferdata(long long b, t_data *data, long long len);
long long		ft_count_of_digits(long long n);
void			ft_printf_s_with_flags(int len, t_data *data);
void			print_pole_and_bufferdata(long long len, t_data *data);
void			buffd_llu(unsigned long long b, t_data *d, long long l, int bs);
long long		ft_count_of_digits_llu(unsigned long long n, int base);
void			ft_printf_u(t_data *data);
void			ft_printf_o(t_data *data);
void			ft_printf_b(t_data *data);
void			get_parametr_pole(t_data *data, long long len);
void			fill_a_string_with_char(char c, char *str, int len);
int				find_symbol(char c, char *macros);
int				count_of_second_part(t_data *data);
void			get_str_xx(unsigned long long int nb, t_data *data);
void			ft_printf_xx_with_flags(t_data *data, int len);
void			ft_printf_mas_c(t_data *data);
void			ft_printf_mas_i(t_data *data);
char			**ft_new_ar_c(int a, int b);
int				**ft_new_arr_i(int a, int b);

#endif
