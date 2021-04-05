/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeckard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:08:14 by hdeckard          #+#    #+#             */
/*   Updated: 2019/10/21 18:18:04 by hdeckard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 10000

typedef struct		s_gnl
{
	char			*buf;
	char			*ost;
	char			*tmp_line;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;
int					get_next_line(const int fd, char **line);

#endif
