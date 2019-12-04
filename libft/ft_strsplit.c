/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:03:26 by qmartina          #+#    #+#             */
/*   Updated: 2019/04/18 12:24:32 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int i;
	int nb;
	int flag;

	i = 0;
	flag = 1;
	nb = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			flag = 1;
		if (flag == 1 && s[i] != c)
		{
			flag = 0;
			nb++;
		}
		i++;
	}
	return (nb);
}

static int	ft_wordln(char const *s, char c)
{
	int	ln;

	ln = 0;
	while (*s != c && *s != '\0')
	{
		ln++;
		s++;
	}
	return (ln);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		nb;

	i = 0;
	if (!s)
		return (NULL);
	nb = ft_words(s, c);
	arr = (char**)malloc(sizeof(*arr) * nb + 1);
	if (!arr)
		return (NULL);
	while (i < nb)
	{
		while (*s == c && *s != '\0')
			s++;
		arr[i] = ft_strsub(s, 0, ft_wordln(s, c));
		if (!arr[i])
			return (NULL);
		s = s + ft_wordln(s, c);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
