/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:22:02 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:39:05 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	while (*(s1 + i) == *(s2 + i) && *(s1 + i) && *(s2 + i) && --n)
		i++;
	return (*(unsigned char*)(s1 + i) - *(unsigned char*)(s2 + i));
}
