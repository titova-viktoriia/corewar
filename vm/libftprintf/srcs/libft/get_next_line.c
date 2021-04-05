/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:07:53 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/02 21:53:03 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*ft_find_or_create_list(int fd, t_gnl **flist)
{
	t_gnl	*list;

	list = *flist;
	while (list)
	{
		if ((int)list->fd == fd)
			return (list);
		list = list->next;
	}
	if (!(list = malloc(sizeof(t_gnl))))
		return (NULL);
	if (!(list->buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
	{
		free(list);
		return (NULL);
	}
	list->fd = fd;
	list->ost = NULL;
	list->tmp_line = NULL;
	if (*flist)
		list->next = *flist;
	*flist = list;
	return (list);
}

static void		ft_split_buf(t_gnl *list)
{
	size_t	i;
	char	*lost;

	i = 0;
	lost = ft_strdup(list->ost);
	ft_strdel(&list->ost);
	while (lost[i] != '\n' && lost[i] != '\0')
		i++;
	list->tmp_line = ft_strsub(lost, 0, i);
	if (ft_strlen(lost) > (i + 1))
		list->ost = ft_strsub(lost, i + 1, (ft_strlen(lost) - (i + 1)));
	ft_strdel(&lost);
}

static void		ft_read_line(t_gnl *list, int *readed)
{
	char	*tmp;
	int		i;

	while ((i = read(list->fd, list->buf, BUFF_SIZE)) > 0)
	{
		list->buf[i] = '\0';
		if (list->ost != NULL)
		{
			tmp = ft_strjoin(list->ost, list->buf);
			ft_strdel(&list->ost);
		}
		else
			tmp = ft_strdup(list->buf);
		list->ost = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (ft_strchr(list->buf, '\n') != NULL)
			return ;
	}
	*readed = i;
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*f_list;
	t_gnl			*list;
	int				readed;

	readed = 1;
	list = ft_find_or_create_list(fd, &f_list);
	if (fd < 0 || !line
		|| BUFF_SIZE <= 0 || read(fd, list->buf, 0) < 0)
		return (-1);
	if ((list->ost != NULL && ft_strchr(list->ost, '\n') != NULL))
		ft_split_buf(list);
	else
	{
		ft_read_line(list, &readed);
		if (readed == 0 && list->ost == NULL)
			return (0);
		ft_split_buf(list);
	}
	*line = ft_strdup(list->tmp_line);
	ft_strdel(&list->tmp_line);
	return (1);
}
