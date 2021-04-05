/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:47:56 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/22 14:07:45 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define LD_EXP_SHIFT 0x3FFF
# define LN_EXP_SHIFT 0x7FFFFFFF

# define LN_SIZE 2

# define LINT_SIZE 278
# define LINT_OVER 1000000000000000000U

typedef struct			s_flags
{
	unsigned int	is_sharp : 1;
	unsigned int	is_zero : 1;
	unsigned int	is_minus : 1;
	unsigned int	is_plus : 1;
	unsigned int	is_space : 1;
	unsigned int	is_h : 1;
	unsigned int	is_hh : 1;
	unsigned int	is_l : 1;
	unsigned int	is_ll : 1;
	unsigned int	is_j : 1;
	unsigned int	is_z : 1;
	unsigned int	is_upcase_l : 1;
	unsigned int	is_precision : 1;
	unsigned int	is_upcase : 1;
	unsigned int	is_pointer : 1;
	unsigned int	is_wildcard : 1;
	unsigned int	is_inf : 1;
	unsigned int	is_nan : 1;
	unsigned int	is_over : 1;
	unsigned int	is_decimal : 1;
}						t_flags;

typedef union			u_long_double
{
	long double			ld;
	struct
	{
		unsigned long	m : 64;
		unsigned int	e : 15;
		unsigned int	s : 1;
	}					s_ld;
}						t_ld;

typedef struct			s_long_number
{
	unsigned int		exp;
	unsigned long		mnt[LN_SIZE];
}						t_ln;

typedef struct			s_big_int
{
	unsigned long		num[LINT_SIZE + 2];
}						t_bi;

typedef struct			s_printf
{
	char		*fmt;
	va_list		ap;
	t_flags		f;
	int			len;
	int			width;
	int			precision;
	int			padding;
	int			printed;
	int			fd;
}						t_printf;

int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
void					parse_format(t_printf *p);
void					ft_putnb_printf(t_printf *p);
void					ft_putnb_printf_2(t_printf *p);
void					ft_putnb_printf_8(t_printf *p);
void					ft_putnb_printf_10(t_printf *p);
void					ft_putnb_printf_16(t_printf *p);
void					ft_putnb_printf_no_base(t_printf *p);
void					ft_putnb_printf_base(t_printf *p, int base);
void					ft_itoa_base_set(uintmax_t n, int b, char *s,
																t_printf *p);
void					padding_left(t_printf *p);
void					padding_right(t_printf *p);
void					ft_putdbl_printf(t_printf *p);
void					ft_itoa_base_printf(uintmax_t n, int b, t_printf *p);
void					ft_putptr_printf(t_printf *p);
void					ft_putchar_printf(t_printf *p);
void					ft_putstr_printf(t_printf *p);
size_t					ft_wcharlen(unsigned wc);
void					ft_putwchar(t_printf *p, unsigned wc, int len,
																int bytes);
void					change_colour(t_printf *p);
void					ft_printf_ld(t_printf *p, char *s, char *n, char *d);
t_bi					ldtobi(long double ld);
t_bi					ldtobi_2(unsigned long mnt, int exp);
t_bi					bi_add(t_bi a, t_bi b);
char					*bitostr(unsigned long a, int len, char filler,
															char *str);
t_ln					ldtoln(long double ld);
unsigned long			lntoul(t_ln ln);
t_ln					ln_sub(t_ln n1, t_ln n2);
t_ln					ln_mul(t_ln n, unsigned long i);
t_ln					ln_highshift(t_ln n, unsigned int shift);
t_ln					ln_lowshift(t_ln n, unsigned int shift);
int						ln_cmp(t_ln n1, t_ln n2);
void					over(long double n, t_printf *p);
void					over1(unsigned long i, t_printf *p, char *str,
															unsigned long a);

#endif
