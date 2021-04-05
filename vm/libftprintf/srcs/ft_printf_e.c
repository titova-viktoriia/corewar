/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_eE.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:20 by hdeckard          #+#    #+#             */
/*   Updated: 2019/11/23 15:47:35 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			count_of_digits_without_sign_for_e(int count)
{
	int		i;
	int		n;

	i = 1;
	n = count;
	if (n < 0)
		n = n * (-1);
	if (n < 10)
		return (2);
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char				*get_e_str_3(int count, char e)
{
	char		*str;
	size_t		len;

	len = 2 + count_of_digits_without_sign_for_e(count);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	fill_a_string_with_char('0', str, len);
	str[0] = e;
	if (count < 0)
	{
		str[1] = '-';
		count = count * (-1);
	}
	else
		str[1] = '+';
	while (count > 0)
	{
		str[len - 1] = count % 10 + '0';
		count = count / 10;
		len--;
	}
	return (str);
}

void				get_e_str_2(int count, t_data *data, long double e)
{
	char			*str;
	char			*str_2;

	get_float_str(e, data);
	str_2 = get_e_str_3(count, data->type);
	str = ft_strjoin(data->bufferdata, str_2);
	ft_strdel(&data->bufferdata);
	data->bufferdata = ft_strdup(str);
	free(str);
	free(str_2);
}

void				get_e_str(long double nb, t_data *data)
{
	int				count;
	long double		e;

	count = 0;
	e = nb;
	if (e < 0)
		e = e * (-1);
	if (nb >= 1)
	{
		while (e >= 10)
		{
			e = e / 10;
			count++;
		}
	}
	if (nb < 1)
	{
		while ((int)e % 10 == 0)
		{
			e = e * 10;
			count--;
		}
	}
	get_e_str_2(count, data, e);
}

void				ft_printf_e(t_data *data)
{
	long double		b;
	size_t			len;

	if (data->flag_large_l == 0)
		b = (double)va_arg(data->args, double);
	if (data->flag_large_l == 1)
		b = (long double)va_arg(data->args, long double);
	get_e_str(b, data);
	len = ft_strlen(data->bufferdata);
	if (data->width > len)
		ft_printf_fe_flags((long double)b, len, data);
	else
	{
		if (b < 0)
			ft_putchar_with_counter('-', data);
		else if (b > 0 && data->flag_plus == 0 && data->flag_space == 1)
			ft_putchar_with_counter(' ', data);
		else if (b >= 0 && data->flag_plus == 1)
			ft_putchar_with_counter('+', data);
		ft_putstr_with_counter(data->bufferdata, data);
	}
	free(data->bufferdata);
}
