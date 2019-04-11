/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:09:53 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:37:21 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (dst < src && len)
		while (len-- && ++i)
			*((unsigned char*)dst)++ = *((unsigned char*)src)++;
	if (src < dst && len)
		while (len--)
			*((unsigned char*)dst + len) = *((unsigned char*)src + len);
	return ((unsigned char*)dst - i);
}
