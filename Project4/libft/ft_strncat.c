/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 14:57:37 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:39:01 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *save;

	save = s1;
	s1 += ft_strlen(s1);
	while (n-- && *s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return (save);
}
