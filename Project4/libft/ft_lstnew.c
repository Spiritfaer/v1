/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:09:35 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:36:54 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *d;

	if (!(d = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		d->content = NULL;
		d->content_size = 0;
	}
	else
	{
		if (!(d->content = malloc(content_size)))
		{
			free(d);
			return (NULL);
		}
		ft_memcpy(d->content, content, content_size);
		d->content_size = content_size;
	}
	d->next = NULL;
	return (d);
}
