/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:16:41 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/18 20:59:19 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 != NULL && s2 != NULL)
	{
		if (!n)
			return (1);
		while (*s1 == *s2 && n--)
			if (*s1++ == '\0' || *s2++ == '\0' || !n)
				return (1);
	}
	return (0);
}
