/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:19:10 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:39:12 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t siz)
{
	char *test;

	if ((test = malloc(siz + (sizeof(char)))) == NULL)
		return (NULL);
	(void)ft_memcpy(test, str, siz);
	*(test + siz) = '\0';
	return (test);
}
