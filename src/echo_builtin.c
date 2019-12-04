/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:46:29 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:46:30 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		ft_strf_ind(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*find_var(char *dop, char **envl)
{
	int		i;
	char	*dopd;

	i = 0;
	dopd = ft_strjoin(dop, "=");
	while (envl[i])
	{
		if (ft_strstr(envl[i], dopd) == envl[i])
		{
			if (!(dop = ft_strsub(envl[i], ft_strlen(dopd),
					ft_strlen(envl[i]) - ft_strlen(dopd))))
				return (NULL);
			ft_strdel(&dopd);
			return (dop);
		}
		i++;
	}
	ft_strdel(&dopd);
	return (NULL);
}

int		dop_echo(char **mas, int i, int c, char **envl)
{
	char	*dop;
	char	*tmp;

	while (mas[i][c] != '\0')
		if (mas[i][c] == '$')
		{
			if (!(dop = ft_strsub(mas[i], c + 1,
								  ft_strf_ind(&mas[i][c + 1], '$') == -1
			? ft_strlen(mas[i]) - c : ft_strf_ind(&mas[i][c + 1], '$'))))
				return (ft_error(15));
			if (!(tmp = find_var(dop, envl)))
				return (0);
			c += 1 + (ft_strf_ind(&mas[i][c + 1], '$') == -1 ?
			(int)ft_strlen(mas[i]) - c : ft_strf_ind(&mas[i][c + 1], '$'));
			ft_putstr(tmp);
			ft_strdel(&dop);
			ft_strdel(&tmp);
		}
		else
		{
			ft_putchar(mas[i][c]);
			c++;
		}
	return (0);
}

int		do_echo(char *line, char **envl)
{
	char	**mas;
	int		i;
	int		c;

	i = 1;
	if (!line || *line == '\0')
		return (0);
	if (!(mas = ft_split_echo(line, " \t")))
		return (ft_error(9));
	while (mas[i])
	{
		c = 0;
		if (dop_echo(mas, i, c, envl) == -1)
			return (ft_error(9));
		ft_putchar(' ');
		i++;
	}
	free_dmas(&mas);
	ft_putchar('\n');
	return (0);
}
