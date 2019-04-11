/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:10:38 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:39:23 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle || haystack == needle)
		return ((char*)haystack);
	while ((*haystack && *needle) && len-- >= ft_strlen(needle))
	{
		if (ft_memcmp(haystack, needle, ft_strlen(needle)) == 0)
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
