/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 15:00:49 by bcharity          #+#    #+#             */
/*   Updated: 2019/05/12 12:29:59 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				to_line(char **line, t_list *node, int ret, int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (((char*)node->content)[i] != '\n'
		&& ((char*)node->content)[i] != '\0')
		i++;
	if (((char*)node->content)[i] == '\n')
	{
		*line = ft_strsub(node->content, 0, i);
		tmp = ft_strdup((node->content) + i + 1);
		free(node->content);
		node->content = tmp;
	}
	else if (((char*)node->content)[i] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(node->content);
		ft_strclr(node->content);
		free(node->content);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int					ret;
	static	t_list		*head;
	t_list				*node;
	char				*tmp;
	char				buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || fd > MAX_FD || BUFF_SIZE == 0)
		return (-1);
	node = find_fd(&head, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = node->content;
		node->content = ft_strjoin(node->content, buf);
		free(tmp);
		if (ft_strrchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (ret < BUFF_SIZE && !ft_strlen(node->content))
	{
		return (0);
	}
	return (to_line(line, node, ret, fd));
}

t_list			*find_fd(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(file, tmp);
	tmp = *file;
	return (tmp);
}
