/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:19:25 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:39:08 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (len--)
	{
		if (i < ft_strlen(src))
			*(dst + i) = *(src + i);
		else
			*(dst + i) = '\0';
		i++;
	}
	return (dst);
}
