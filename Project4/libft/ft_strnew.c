/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:39:01 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/15 17:32:11 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tmp;

	if ((tmp = (char*)malloc(size + 1)) == NULL)
		return (NULL);
	ft_memset(tmp, '\0', size + 1);
	return (tmp);
}
