/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:39:48 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/12/19 11:34:47 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	parse_flags(t_printf *p)
{
	while (*p->fmt == '#' || *p->fmt == '0' || *p->fmt == '-'
			|| *p->fmt == '+' || *p->fmt == ' ')
	{
		if (*p->fmt == '#')
			p->f.is_sharp = 1;
		if (*p->fmt == '0')
			p->f.is_zero = 1;
		if (*p->fmt == '-')
			p->f.is_minus = 1;
		if (*p->fmt == '+')
			p->f.is_plus = 1;
		if (*p->fmt == ' ')
			p->f.is_space = 1;
		p->fmt++;
	}
	if (p->f.is_minus)
		p->f.is_zero = 0;
	if (p->f.is_plus)
		p->f.is_space = 0;
}

static inline void	parse_width(t_printf *p)
{
	p->width = 0;
	if (*p->fmt == '*')
	{
		p->width = (int)va_arg(p->ap, int);
		p->fmt++;
	}
	if (p->width < 0)
	{
		p->f.is_minus = 1;
		p->width = -p->width;
	}
	if ('0' <= *p->fmt && *p->fmt <= '9')
	{
		p->width = 0;
		while ('0' <= *p->fmt && *p->fmt <= '9')
			p->width = 10 * p->width + *p->fmt++ - '0';
	}
}

static inline void	parse_precision(t_printf *p)
{
	p->f.is_precision = 0;
	p->precision = 0;
	if (*p->fmt == '.' && ++p->fmt)
	{
		if (*p->fmt == '*')
		{
			p->precision = (int)va_arg(p->ap, int);
			p->fmt++;
			if (p->precision < 0)
			{
				p->precision = 0;
				p->f.is_wildcard = 1;
			}
		}
		else if ('0' <= *p->fmt && *p->fmt <= '9')
		{
			while ('0' <= *p->fmt && *p->fmt <= '9')
				p->precision = 10 * p->precision + *p->fmt++ - '0';
		}
		p->f.is_precision = 1;
	}
}

static inline void	parse_length_modifier(t_printf *p)
{
	while (1)
	{
		if (*p->fmt == 'h' && p->fmt[1] == 'h' && ++p->fmt)
			p->f.is_hh = 1;
		else if (*p->fmt == 'h')
			p->f.is_h = 1;
		else if (*p->fmt == 'l' && p->fmt[1] == 'l' && ++p->fmt)
			p->f.is_ll = 1;
		else if (*p->fmt == 'l')
			p->f.is_l = 1;
		else if (*p->fmt == 'j')
			p->f.is_j = 1;
		else if (*p->fmt == 'z')
			p->f.is_z = 1;
		else if (*p->fmt == 'L')
			p->f.is_upcase_l = 1;
		else if (*p->fmt == '.' || *p->fmt == '1' || *p->fmt == '2')
			;
		else
			break ;
		p->fmt++;
	}
}

void				parse_format(t_printf *p)
{
	ft_bzero(&p->f, sizeof(p->f));
	parse_flags(p);
	parse_width(p);
	parse_precision(p);
	parse_length_modifier(p);
	parse_flags(p);
	if ('A' <= *p->fmt && *p->fmt <= 'Z')
		p->f.is_upcase = 1;
}
