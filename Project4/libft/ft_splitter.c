/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:15:48 by istalevs          #+#    #+#             */
/*   Updated: 2017/12/13 12:27:55 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_splitter(const char *s, char c)
{
	int count;
	int word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != '\0' && *s != c)
			count++;
		if ((*(s + 1) == '\0' || *s == c) && count > 0)
		{
			word++;
			count = 0;
		}
		s++;
	}
	return (word);
}
