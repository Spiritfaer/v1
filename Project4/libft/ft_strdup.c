/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:50:09 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:38:25 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	siz;
	char	*test;

	siz = ft_strlen(str) + 1;
	if ((test = malloc(siz)) == NULL)
		return (NULL);
	(void)ft_memcpy(test, str, siz);
	return (test);
}
