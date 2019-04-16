/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:11:42 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:36:08 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double_t	ft_atof(const char* str)
{
	double_t	res_one;
	double_t	res_two;
	double_t	count;
	int8_t		neg;

	res_one = 0.0;
	res_two = 0.0;
	neg = 1;
	count = 1;
	while (ft_isspase(*str))
		str++;
	if (*str == 45 || *str == 43)
		neg = -(*str++ - 44);

	while (ft_isdigit(*str))
		res_one = (res_one * 10) + (double_t)(*str++ - 48);
	if (*str++ == '.')
		while (ft_isdigit(*str) && (count *= 10))
			res_two = (res_two * 10) + (double_t)(*str++ - 48);
	return ((res_one + (res_two / count)) * neg);
}
