/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:01:16 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:37:02 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (n--)
	{
		*((unsigned char*)dst + i) = *((unsigned char*)src + i);
		if ((*(unsigned char*)src + i++) == (unsigned char)c)
			return ((unsigned char*)dst + i);
	}
	return (NULL);
}
