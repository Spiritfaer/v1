/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:13:46 by istalevs          #+#    #+#             */
/*   Updated: 2018/02/04 16:35:58 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_min_itoa(int n, char **str)
{
	size_t	size;
	int		count;

	size = 0;
	count = n;
	while (++size && (count /= 10))
		;
	size++;
	if (!(*str = ft_strnew(size)))
		return ;
	while (size--)
	{
		*(*str + (size)) = (char)(48 - (n % 10));
		n /= 10;
	}
	**str = 45;
}

static void	ft_null_itoa(int n, char **str)
{
	if (!(*str = ft_strnew(1)))
		return ;
	**str = (char)(n + 48);
}

static void	ft_max_itoa(int n, char **str)
{
	size_t	size;
	int		count;

	size = 0;
	count = n;
	while (++size && (count /= 10))
		;
	if (!(*str = ft_strnew(size)))
		return ;
	while (size--)
	{
		*(*str + (size)) = (char)(48 + (n % 10));
		n /= 10;
	}
}

char		*ft_itoa(int n)
{
	char	*num;

	num = NULL;
	if (n < 0)
		ft_min_itoa(n, &num);
	if (n == 0)
		ft_null_itoa(n, &num);
	if (n > 0)
		ft_max_itoa(n, &num);
	if (num == NULL)
		return (NULL);
	return (num);
}
