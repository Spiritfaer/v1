/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 12:38:30 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:37:06 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *end;
	unsigned char *start;

	end = (unsigned char*)s + n;
	start = (unsigned char*)s;
	while (n-- && !(*start == (unsigned char)c))
		start++;
	if (start >= end)
		return (NULL);
	if (*start == (unsigned char)c)
		return ((void*)start);
	return (NULL);
}
