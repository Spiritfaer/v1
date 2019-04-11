/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:17:26 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:38:44 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		dlen;

	d = dst;
	s = src;
	n = dstsize;
	while (n-- != 0 && *d != '\0' && d++)
		;
	dlen = d - dst;
	if ((n = dstsize - dlen) == 0)
		return (dlen + ft_strlen(s));
	while (n-- > 1 && (*d++ = *s++) != '\0')
		;
	*d = '\0';
	return (dlen + ft_strlen(src));
}
