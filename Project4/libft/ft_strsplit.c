/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 20:13:04 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/15 19:06:13 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	const char	*tmp;
	char		**demo;
	int			words;
	int			count;

	if (s == NULL)
		return (NULL);
	count = 0;
	words = ft_splitter(s, c) + 1;
	if ((demo = (char**)malloc(words * sizeof(char*))) == NULL)
		return (NULL);
	(void)ft_memset(demo, '\0', words-- * sizeof(char*));
	while (count < words)
	{
		while (*s && *s == c)
			s++;
		tmp = s;
		while (*tmp && *tmp != c)
			tmp++;
		if (*tmp == c || *tmp == '\0')
			if ((demo[count++] = ft_strndup(s, (tmp++ - s))) == NULL)
				return (NULL);
		s = tmp;
	}
	return (demo);
}
