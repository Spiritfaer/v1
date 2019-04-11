/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:49:59 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/15 18:48:09 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	char	*save;
	size_t	size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = (sizeof(char) * ft_strlen(s1)) + (sizeof(char) * ft_strlen(s2));
	if ((tmp = (char*)malloc(size + 1)) == NULL)
		return (NULL);
	save = tmp;
	while ((*tmp++ = *s1++) != '\0')
		;
	--tmp;
	while ((*tmp++ = *s2++) != '\0')
		;
	*tmp = '\0';
	return (save);
}
/*
**	заменить функции копирования
*/
