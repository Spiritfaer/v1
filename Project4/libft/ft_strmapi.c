/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:57:51 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:38:57 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tmp;
	char	*save;
	int		i;

	if (!s || !f)
		return (NULL);
	if ((tmp = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	save = tmp;
	i = 0;
	while (*s)
		*tmp++ = f(i++, *s++);
	*tmp = '\0';
	return (save);
}
