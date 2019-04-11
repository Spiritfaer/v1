/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 21:44:38 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:36:40 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (alst && del)
	{
		while (*alst)
		{
			del((*alst)->content, (*alst)->content_size);
			tmp = *alst;
			*alst = (*alst)->next;
			free(tmp);
			tmp = NULL;
		}
	}
}
