/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 21:38:17 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/15 17:49:49 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char *start;
	char *end;
	char *tmp;
	char *save;

	if (s == NULL)
		return (NULL);
	while (ft_isspase(*s))
		s++;
	start = (char*)s;
	s += ft_strlen(s);
	while (ft_isspase(*--s) && *start != '\0')
		;
	end = (char*)s;
	if ((tmp = (char*)malloc(sizeof(char) * (++end - start + 1))) == NULL)
		return (NULL);
	save = tmp;
	while (start != end)
		*tmp++ = *start++;
	*tmp = '\0';
	return (save);
}

/*
**	strsub?
*/
