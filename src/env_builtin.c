3/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 06:05:20 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 06:05:23 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		sort_env(char **mas)
{
	int		d;
	int		i;
	int		len;
	char	*dop;

	d = 0;
	len = 0;
	while (mas[len])
		len++;
	while (d < len)
	{
		i = 0;
		while (mas[i + 1])
		{
			if (ft_strcmp(mas[i], mas[i + 1]) > 0)
			{
				dop = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = dop;
			}
			i++;
		}
		d++;
	}
	return (0);
}

int		full_env(char **mas, char ***envl)
{
	int		len;
	char	**dopenvl;
	char	*dopstr;

	dopenvl = *envl;
	if (ft_strcmp(mas[0], "env") == 0)
		return (show_env(*envl));
	else
	{
		len = 0;
		while (dopenvl[len] != NULL)
		{
			if (!(dopstr = ft_strjoin(mas[1], "=")))
				return (-1);
			if (ft_strstr(dopenvl[len], dopstr) == dopenvl[len])
				dopenvl[len][0] = -128;
			len++;
			ft_strdel(&dopstr);
		}
		return (ft_dopenv(mas, envl));
	}
}

int		ft_dop_setenv(char **mas, int i, char ***dopenvld, char ***envl)
{
	char	**dopenvl;

	dopenvl = *dopenvld;
	if (!(dopenvl[i] = (char *)ft_memalloc(sizeof(char *) *
			(ft_strlen(mas[1]) + ft_strlen(mas[2]) + 2))))
		return (-1);
	ft_strcat(dopenvl[i], mas[1]);
	ft_strcat(dopenvl[i], "=");
	ft_strcat(dopenvl[i], mas[2]);
	i++;
	dopenvl[i] = NULL;
	return (0);
}

int		ft_setenv(char **mas, char ***envl, char **dopmas, int type)
{
	int		i;
	char	**dopenvl;
	int		c;

	i = 0;
	c = -1;
	if (!(dopenvl = (char **)ft_memalloc(sizeof(char **) *
			(ft_maslen_with(dopmas) + 1 + type))))
		return (-1);
	while (dopmas[++c] != NULL)
		if (dopmas[c][0] != -128)
		{
			if (!(dopenvl[i] = (char *)ft_memalloc(sizeof(char *)
					* ft_strlen(dopmas[c]))))
				return (-1);
			ft_strcpy(dopenvl[i], dopmas[c]);
			dopenvl[i][ft_strlen(dopmas[c]) + 1] = '\0';
			i++;
		}
	if (type == 1)
		ft_dop_setenv(mas, i, &dopenvl, envl);
	free_dmas(envl);
	*envl = dopenvl;
	return (0);
}

int		show_env(char **mas)
{
	int		n;

	n = 0;
	if (sort_env(mas) == -1)
		return (0);
	while (mas[n])
	{
		ft_printf("%s\n", mas[n]);
		n++;
	}
	return (0);
}
