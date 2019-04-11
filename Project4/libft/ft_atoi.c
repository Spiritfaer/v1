/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:11:42 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:36:08 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long long int	dst;
	long long int	neg;
	size_t			count;

	dst = 0;
	neg = 1;
	count = 0;
	while (ft_isspase(*str))
		str++;
	if (*str == 45 || *str == 43)
		*str++ > 43 ? neg = -1 : 0;
	while (ft_isdigit(*(str + count)))
		count++;
	while (ft_isdigit(*str))
	{
		if (count >= 19 || dst > 9223372036854775807)
			return (neg == -1 ? 0 : -1);
		dst = (dst * 10) + (long long int)(*str++ - 48);
	}
	return ((int)(dst * neg));
}
