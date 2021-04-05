/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xX.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:14:40 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 16:33:22 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				ft_printf_xx_without_flags(t_data *data)
{
	if (data->flag_hash == 1)
	{
		ft_putchar_with_counter('0', data);
		ft_putchar_with_counter(data->type, data);
	}
	ft_putstr_with_counter(data->bufferdata, data);
}

static void				ft_printf_xx_with_flags_part_2(t_data *data, int len)
{
	if (data->flag_hash == 1)
		len = len + 2;
	print_in_while(' ', data->width - len, data);
	if (data->flag_hash == 1)
	{
		ft_putchar_with_counter('0', data);
		ft_putchar_with_counter(data->type, data);
	}
	ft_putstr_with_counter(data->bufferdata, data);
}

void					ft_printf_xx_with_flags(t_data *data, int len)
{
	if (data->flag_minus == 1)
	{
		if (data->flag_hash == 1)
		{
			ft_putchar_with_counter('0', data);
			ft_putchar_with_counter(data->type, data);
			len = len + 2;
		}
		ft_putstr_with_counter(data->bufferdata, data);
		print_in_while(' ', data->width - len, data);
	}
	else if (data->flag_zero == 1)
	{
		if (data->flag_hash == 1)
		{
			ft_putchar_with_counter('0', data);
			ft_putchar_with_counter(data->type, data);
			len = len + 2;
		}
		print_in_while('0', data->width - len, data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
	else
		ft_printf_xx_with_flags_part_2(data, len);
}

void					get_str_xx(unsigned long long int nb, t_data *data)
{
	int		count;
	char	*str;
	char	*str_2;

	count = count_of_digits_16(nb);
	if (nb == 0 && data->type != 'p')
		data->flag_hash = 0;
	if (data->precision > -1)
		data->flag_zero = 0;
	if (nb == 0 && (data->precision == 0
	|| (data->precision == -1 && data->flag_dot == 1)))
		data->bufferdata = NULL;
	else if (data->precision <= count)
		data->bufferdata = ft_itoa_from_10_to_16(nb, data);
	else
	{
		str = (char *)malloc(sizeof(char) * (data->precision - count + 1));
		str[data->precision - count] = '\0';
		fill_a_string_with_char('0', str, data->precision - count);
		str_2 = ft_itoa_from_10_to_16(nb, data);
		data->bufferdata = ft_strjoin(str, str_2);
		ft_strdel(&str);
		ft_strdel(&str_2);
	}
}

void					ft_printf_xx(t_data *data)
{
	unsigned long long int	add;
	size_t					len;

	if (data->flag_l == 0 && data->flag_h == 0)
		add = (unsigned)va_arg(data->args, int);
	else if (data->flag_l == 1)
		add = (unsigned long)va_arg(data->args, long int);
	else if (data->flag_l > 1)
		add = (unsigned long long)va_arg(data->args, long long int);
	else if (data->flag_h == 1)
		add = (unsigned short)va_arg(data->args, int);
	else
		add = (unsigned char)va_arg(data->args, int);
	get_str_xx(add, data);
	if (data->bufferdata == NULL)
		len = 0;
	else
		len = ft_strlen(data->bufferdata);
	if (data->width > len)
		ft_printf_xx_with_flags(data, len);
	else
		ft_printf_xx_without_flags(data);
	free(data->bufferdata);
}
