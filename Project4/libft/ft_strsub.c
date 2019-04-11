/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:46:28 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/15 17:45:48 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *tmp;
	char *save;

	if (s == NULL)
		return (NULL);
	if ((tmp = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	save = tmp;
	while (len-- && s[start])
		*tmp++ = s[start++];
	*tmp = '\0';
	return (save);
}
