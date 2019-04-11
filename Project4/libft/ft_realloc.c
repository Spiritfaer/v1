/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 23:10:46 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:37:59 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void *tmp;

	if (!ptr && size)
	{
		if (!(tmp = malloc(size)))
			return (NULL);
		ft_memset(tmp, '\0', size);
		return (tmp);
	}
	if (ptr && !size)
	{
		free(ptr);
		return (NULL);
	}
	if (!(tmp = malloc(size)))
		return (NULL);
	ft_memset(tmp, '\0', size);
	ft_memcpy(tmp, ptr, size);
	free(ptr);
	return (tmp);
}
