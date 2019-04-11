/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:21:15 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:39:39 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	if (*needle == 0)
		return ((char*)haystack);
	while (*haystack && *needle)
	{
		if (ft_memcmp(haystack, needle, ft_strlen(needle)) == 0)
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
