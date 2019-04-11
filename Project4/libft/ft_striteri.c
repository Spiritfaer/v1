/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:28:55 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:38:34 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_striteri(char *s, void (*f)(unsigned int c, char *str))
{
	unsigned int i;

	i = 0;
	if (s != NULL && f != NULL)
		while (*s)
			f(i++, s++);
}
