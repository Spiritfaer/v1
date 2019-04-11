/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:23:26 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:38:53 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *str, char (*f)(char))
{
	char *tmp;
	char *ret;

	if (!str || !f)
		return (NULL);
	if ((tmp = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)) == NULL)
		return (NULL);
	ret = tmp;
	while (*str)
		*tmp++ = f(*str++);
	*tmp = '\0';
	return (ret);
}
