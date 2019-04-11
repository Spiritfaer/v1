/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:29:47 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:36:51 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	new = tmp;
	while (lst->next)
	{
		tmp->next = f(lst->next);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (new);
}
