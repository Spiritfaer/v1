/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:53:00 by istalevs          #+#    #+#             */
/*   Updated: 2018/02/18 12:15:37 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_make_list(size_t fd, t_list **head)
{
	t_list	*save;
	t_list	*new;

	save = *head;
	while (save && save->content_size != fd)
		save = save->next;
	if (!save)
	{
		if (!(new = (t_list*)malloc(sizeof(t_list))))
			return (-1);
		new->content_size = fd;
		new->content = NULL;
		ft_lstadd(head, new);
	}
	return (0);
}

int64_t		ft_fd_struct(size_t fd, t_list *head)
{
	char	*buff;
	size_t	read_size = 0;
	size_t	one_read_size = 0;
	size_t	count;

	if (!(buff = (char*)malloc(BUFF_SIZE + 1)))
		return (-1);
	*(buff) = '\0';
	count = 0;
	while (head->content_size != fd)
		head = head->next;
	read_size = (head->content) ? ft_strlen((char*)head->content) : 0;
	if (!(head->content))
		head->content = ft_realloc(head->content, read_size + 1);
	while (!ft_strchr(head->content, '\n')
	&& (one_read_size = _read((int)fd, buff, BUFF_SIZE)) > 0 && ++count)
	{
		read_size += one_read_size;
		head->content = ft_realloc(head->content, read_size + 1);
		ft_strlcat(head->content, buff, read_size + 1);
	}
	if (read_size > 0)
		count++;
	free(buff);
	return (count);
}

void		ft_struct_line(size_t fd, t_list *head, char **line)
{
	char	*end;
	char	*tmp;
	char	**str;
	size_t	s_tmp;

	while (head->content_size != fd)
		head = head->next;
	str = (char**)(&(head->content));
	end = ft_strchr(*str, '\n');
	if (!ft_strlen(*str))
		return ;
	*line = (end != NULL) ? ft_strndup(*str, end - *str)
							: ft_strdup(*str);
	if (end != NULL)
	{
		s_tmp = end - *str;
		tmp = ft_strndup(end + 1, ft_strlen(*str) - s_tmp);
		ft_memdel((void**)str);
		head->content = tmp;
	}
	if (!ft_strcmp(*str, *line) && end == NULL)
		ft_memdel((void**)str);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*head = NULL;
	int64_t			index;

	if (fd < 0 || read(fd, 0, 0) < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (ft_make_list((size_t)fd, &head) < 0)
		return (-1);
	index = ft_fd_struct((size_t)fd, head);
	ft_struct_line((size_t)fd, head, line);
	if (index < 1)
		return (0);
	if (index < 0)
		return (-1);
	return (1);
}
