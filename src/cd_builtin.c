/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:34:06 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:34:07 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		go_to_dir(char *line, char ***envl, char *path)
{
	char	*dopline;
	char	**splitline;
	char	path1[1024];

	if (dop_go_to_dir(line, envl) == -1)
		return (-1);
	if (access(line, 0) != 0)
	{
		ft_printf("can't open folder: %s\n", line);
		return (-1);
	}
	chdir(line);
	ft_bzero(path1, 1024);
	getcwd(path1, sizeof(path1));
	if (!(dopline = ft_strjoin("setenv PWD ", path1))
		|| !(splitline = ft_split_echo(dopline, " ")))
		return (-1);
	if ((full_env(splitline, envl)) == -1)
		return (-1);
	ft_strdel(&dopline);
	free_dmas(&splitline);
	return (0);
}

char	*ft_parse_cd(char **mas, char ***envl, char *homepath)
{
	char	*dopline;
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (!(dopline = (char *)ft_memalloc(sizeof(char) * 1024)))
		return (NULL);
	while (mas[1][i])
	{
		if (mas[1][i] == '~')
		{
			ft_strcpy(&dopline[c], homepath);
			c += (int)ft_strlen(homepath) - 1;
		}
		else
			dopline[c] = mas[1][i];
		i++;
		c++;
	}
	return (dopline);
}

int		do_cd(char **mas, char ***envl)
{
	char	*l;
	char	path[1024];
	char	*hp;

	if (!(hp = find_var("HOME", *envl)))
		return (-1);
	if (ft_maslen(mas) != 1 && ft_maslen(mas) != 2)
		return (ft_error(9));
	if (mas[1] == NULL)
		return (go_to_dir(hp, envl, path));
	else if (ft_strcmp(mas[0], "cd") == 0 &&
	ft_strcmp(mas[1], "-") == 0 && !mas[2])
	{
		if ((!(l = find_var("OLDPWD", *envl)))
		|| go_to_dir(l, envl, path) == -1)
			return (-1);
		ft_strdel(&l);
		ft_strdel(&hp);
		return (0);
	}
	if (!(l = ft_parse_cd(mas, envl, hp)) || go_to_dir(l, envl, path))
		return (-1);
	ft_strdel(&l);
	ft_strdel(&hp);
	return (0);
}
