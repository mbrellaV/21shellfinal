/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_strsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:08:35 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:08:36 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		isdelim(char *a, char b)
{
	if (ispar(b))
		return (2);
	while (*a)
	{
		if (*a == b)
			return (1);
		a++;
	}
	return (0);
}

int		c_size(char *str, char b, char *delim)
{
	int i;
	int dop;

	i = 0;
	str++;
	dop = 0;
	if (*str == b)
		return (-2);
	while (*str && *str != b)
	{
		if (isdelim(delim, *str) == 0 || ispar(*str))
			dop++;
		i++;
		str++;
	}
	if (*str == '\0' && dop > 0)
		return (-1);
	return (i);
}

int		word_size(char *str, char *delim)
{
	int i;

	i = 0;
	if (isdelim(delim, *str) == 2)
		return (c_size(str, *str, delim));
	if (isdelim(delim, str[0]) || *str == '\0')
		return (0);
	while (*str)
	{
		if (isdelim(delim, *str))
			return (i);
		i++;
		str++;
	}
	return (i);
}

int		count_words(char *str, char *delim)
{
	int		i;
	int		dop;

	i = 0;
	while (*str)
	{
		dop = word_size(str, delim);
		if (dop > 0)
		{
			str += dop + (ispar(*str) ? 2 : 0);
			i++;
		}
		else if (dop == -2)
			str += 2;
		else if (dop == -1)
			return (ft_error(9));
		else
			str++;
	}
	return (i);
}

char	**ft_split_echo(char *str, char *delim)
{
	char	**mas;
	int		cn;
	int		i;
	int		cn_words;

	if ((cn_words = count_words(str, delim)) <= 0)
		return (NULL);
	i = 0;
	cn_words++;
	cn = 0;
	if (!(mas = (char **)ft_memalloc(sizeof(char **) * cn_words)))
		return (NULL);
	while (i < (cn_words - 1) && str[cn])
		if (word_size(str + cn, delim) > 0 && str[cn])
		{
			if (!(mas[i] = (char *)ft_strsub(str, cn + (ispar(str[cn]) ? 1 : 0),
					word_size(str + cn, delim))))
				return (!ft_error_with(13, &mas) ? NULL : 0);
			cn += word_size(str + cn, delim) + (ispar(str[cn]) ? 2 : 0);
			i++;
		}
		else
			cn += 1 + (ispar(str[cn]) ? 1 : 0);
	mas[i] = NULL;
	return (mas);
}
