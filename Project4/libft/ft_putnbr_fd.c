/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 16:15:04 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:37:46 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	x;
	int		tmp;
	int		count;
	int		size;

	tmp = n;
	count = 1;
	size = 0;
	while (++size && (tmp /= 10) != 0)
		count *= 10;
	if (n < 0)
	{
		write(fd, "-", 1);
		while (size-- && (x = 48 - n / count) != 0 && write(fd, &x, 1))
			if (n += (x - 48) * count)
				count /= 10;
	}
	else
		while (size-- && (x = 48 + n / count) != 0 && write(fd, &x, 1))
			if (n -= (x - 48) * count)
				count /= 10;
}
