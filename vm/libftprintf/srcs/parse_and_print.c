/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:33 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 22:19:27 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		parse_width_with_star(t_data *data)
{
	int		w;

	w = (int)va_arg(data->args, int);
	if (w < 0)
	{
		w = w * (-1);
		data->flag_minus = 1;
	}
	data->width = w;
}

static int		parse_prec(const char *f, t_data *data, int i)
{
	i++;
	if (f[i] == '*')
	{
		data->precision = (int)va_arg(data->args, int);
		if (data->precision < 0)
			data->precision = -1;
	}
	else if (f[i] <= '9' && f[i] >= '0')
	{
		data->precision = ft_atoi(f + i);
		while (f[i] <= '9' && f[i] >= '0')
			i++;
	}
	else
	{
		data->flag_dot = 1;
		data->precision = 0;
		i--;
	}
	return (i);
}

static void		parse_flags(const char *frmt, t_data *data)
{
	while (find_symbol(frmt[data->index], CHARS) == 1
	&& frmt[data->index] != '\0')
	{
		if (frmt[data->index] == 'l')
			data->flag_l++;
		if (frmt[data->index] == 'h')
			data->flag_h++;
		if (frmt[data->index] == 'L')
			data->flag_large_l = 1;
		if (frmt[data->index] == '0' && frmt[data->index - 1] != '.'
		&& !(frmt[data->index - 1] >= '0' && frmt[data->index - 1] <= '9'))
			data->flag_zero = 1;
		if (frmt[data->index] == '+')
			data->flag_plus = 1;
		if (frmt[data->index] == '-')
			data->flag_minus = 1;
		if (frmt[data->index] == ' ')
			data->flag_space = 1;
		if (frmt[data->index] == '#')
			data->flag_hash = 1;
		data->index++;
	}
}

static void		parse_width_and_precision(const char *f, t_data *d, int i)
{
	while (find_symbol(f[i], CHARS) == 1 && f[i] != '\0')
	{
		if (f[i] == '*' && f[i - 1] != '.')
			parse_width_with_star(d);
		if (f[i] <= '9' && f[i] > '0' && f[i - 1] != '.')
		{
			d->width = ft_atoi(f + i);
			while (f[i] <= '9' && f[i] >= '0')
				i++;
		}
		if (f[i] == '.')
			i = parse_prec(f, d, i);
		i++;
	}
}

void			parse_and_print(t_data *data, const char *format)
{
	while (format[data->index] != '\0')
	{
		if (format[data->index] == '%')
		{
			data->index++;
			parse_width_and_precision(format, data, data->index);
			parse_flags(format, data);
			if (find_symbol(format[data->index], SPEC_TYPE) == 1)
			{
				data->type = format[data->index];
				data->index++;
			}
			if (data->type != '0')
				print_common(data);
			install_data(data);
		}
		else
		{
			ft_putchar_with_counter(format[data->index], data);
			data->index++;
		}
	}
}
