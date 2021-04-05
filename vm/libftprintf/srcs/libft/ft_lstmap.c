/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <hdeckard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:37:44 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/23 16:22:36 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*q;
	t_list	*b;
	t_list	*m;
	t_list	*l;

	if (!lst || !f)
		return (NULL);
	m = f(lst);
	if (!(q = ft_lstnew(m->content, m->content_size)))
		return (NULL);
	b = q;
	lst = lst->next;
	while (lst)
	{
		m = f(lst);
		if (!(l = ft_lstnew(m->content, m->content_size)))
			return (NULL);
		q->next = l;
		q = q->next;
		lst = lst->next;
	}
	q->next = NULL;
	return (b);
}
