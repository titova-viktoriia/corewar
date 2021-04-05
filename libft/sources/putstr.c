/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:56:42 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/11/12 12:01:10 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void		ft_putstr_char(t_printf *p)
{
	unsigned	*s;
	char		*tmp;
	int			len;

	s = va_arg(p->ap, unsigned*);
	if (s == NULL)
		s = (unsigned*)"(null)";
	tmp = (char *)s;
	len = 0;
	while (*tmp++)
		len++;
	p->printed = len;
	if (p->f.is_precision && !p->f.is_wildcard)
		p->printed = p->printed > p->precision ? p->precision : p->printed;
	if ((p->padding = (p->width - p->printed)) < 0)
		p->padding = 0;
	padding_left(p);
	p->len += write(p->fd, s, p->printed);
	padding_right(p);
}

static void		ft_putstr_wchar(t_printf *p)
{
	wchar_t		*w;
	wchar_t		*s;
	int			len;

	w = va_arg(p->ap, wchar_t *);
	if (w == NULL)
		w = (wchar_t*)"(null)";
	len = 0;
	s = w;
	while (*s != L'\0')
		len += ft_wcharlen(*s++);
	p->printed = len;
	if ((p->padding = (p->width - p->printed)) < 0)
		p->padding = 0;
	p->f.is_precision = (p->width > p->precision) ? 0 : 1;
	padding_left(p);
	len = 0;
	while (*w && (p->printed -= len) > 0)
	{
		len = ft_wcharlen(*w);
		ft_putwchar(p, *w++, p->printed, len);
	}
	padding_right(p);
}

void			ft_putstr_printf(t_printf *p)
{
	if (!p->f.is_l && !p->f.is_ll && !p->f.is_upcase)
		ft_putstr_char(p);
	else
		ft_putstr_wchar(p);
}
