/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:12:33 by hdeckard          #+#    #+#             */
/*   Updated: 2019/12/04 21:32:53 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		the_last_number_before_rounding(long double nb, int p)
{
	unsigned long long int			k;
	int								i;
	long double						n;

	i = 1;
	k = 10;
	n = nb;
	while (i <= p)
	{
		if (i % 8 == 0)
		{
			n = n * k;
			n = n - (int)n;
			k = 1;
		}
		k = k * 10;
		i++;
	}
	n = n * k;
	return (n);
}

void			get_2(unsigned long long int fp, int *sp, t_data *data, int i)
{
	int			len;

	len = count_of_second_part(data) + (int)ft_count_of_digits(fp);
	if (!(data->bufferdata = (char *)malloc(sizeof(char) * (len + 1))))
		return ;
	data->bufferdata[len] = '\0';
	fill_a_string_with_char('.', data->bufferdata, len);
	if (data->precision != 0 && !(data->precision == -1 && data->flag_dot == 1))
	{
		while (i > -1)
		{
			data->bufferdata[len - 1] = sp[i] + '0';
			i--;
			len--;
		}
		len--;
	}
	if (data->flag_hash == 1 && (data->precision == 0 || data->flag_dot == 1))
		len--;
	while (len >= 1)
	{
		data->bufferdata[len - 1] = fp % 10 + '0';
		fp = fp / 10;
		len--;
	}
}

void			spart_plus_one(int *spart, int i)
{
	spart[i] = spart[i] + 1;
	while (spart[i] == 10 && i > 0)
	{
		spart[i] = 0;
		i--;
		spart[i] = spart[i] + 1;
	}
}

int				*get_spart(long double nb, int prec, int i)
{
	int				*spart;
	long double		k;

	k = the_last_number_before_rounding(nb, prec);
	spart = (int *)malloc(sizeof(int) * (prec + 1));
	while (i <= prec)
	{
		spart[i] = (unsigned long long int)(nb * 10);
		nb = (nb * 10) - (unsigned long long int)(nb * 10);
		if (i == prec)
		{
			if (spart[i] < (int)((unsigned long long int)k % 10))
			{
				spart[i] = (int)((unsigned long long int)k % 10);
				nb = k - (unsigned long long int)k;
			}
		}
		i++;
	}
	i--;
	if ((spart[i] > 5 && prec != 0) ||
	(spart[i] == 5 && (spart[i - 1] % 2 != 0 || nb != 0) && prec != 0))
		spart_plus_one(spart, i - 1);
	return (spart);
}

void			get_float_str(long double b, t_data *data)
{
	unsigned long long int			first_part;
	int								*spart;

	if (b < 0)
		b = b * (-1);
	if (data->flag_dot == 0 && data->precision == -1)
		data->precision = 6;
	if (data->flag_dot == 1 && data->precision == -1)
		data->precision = 0;
	first_part = (unsigned long long int)b;
	spart = get_spart(b - (unsigned long long int)b, data->precision, 0);
	if (data->precision == 0 && spart[0] > 5)
		first_part = first_part + 1;
	else if (data->precision == 0 && spart[0] == 5 &&
	(first_part % 2 != 0 || (b * 10) - (unsigned long long int)(b * 10) != 0))
		first_part = first_part + 1;
	else if (spart[0] == 10)
	{
		first_part = first_part + 1;
		spart[0] = 0;
	}
	get_2(first_part, spart, data, data->precision - 1);
	free(spart);
}
