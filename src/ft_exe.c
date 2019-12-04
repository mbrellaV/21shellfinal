/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:26:07 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:26:08 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		do_exe(char **mas, char **envl)
{
	g_pid = fork();
	if (g_pid == 0)
	{
		if (execve(mas[0], mas, envl) == -1)
			return (-1);
	}
	else if (g_pid == -1)
	{
		ft_printf("fork error");
		return (-1);
	}
	else
		wait(&g_pid);
	return (1);
}

int		find_exe(char *dir_name, char *filename)
{
	struct dirent	*pdirent;
	DIR				*dire;

	if (dir_name == NULL)
		return (ft_error(10));
	if (!(dire = opendir(dir_name)))
	{
		ft_printf("cant open2: %s: \n", dir_name);
		return (-1);
	}
	while ((pdirent = readdir(dire)) != NULL)
	{
		if (ft_strcmp(pdirent->d_name, filename) == 0)
		{
			closedir(dire);
			return (1);
		}
	}
	closedir(dire);
	return (0);
}

int		dop_func_exe(char **envl, char **mas, int i, char ***dopmas1)
{
	char	*tmp;
	char	*tmp1;
	char	**dopmas;

	dopmas = *dopmas1;
	if (find_exe(dopmas[i], mas[0]) == 1)
	{
		tmp = mas[0];
		tmp1 = ft_strjoin(dopmas[i], "/");
		if (!(mas[0] = ft_strjoin(tmp1, mas[0])))
			return (ft_error(15));
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		do_exe(mas, envl);
		free_dmas(&dopmas);
		return (1);
	}
	return (0);
}

int		do_search(char **envl, char **mas, int i, int d)
{
	char	**dopmas;

	while (envl[d])
	{
		if (ft_strstr(envl[d], "PATH=") == envl[d])
		{
			if (!(dopmas = ft_split_echo(envl[d], "=: ")))
				return (-1);
			i = 1;
			while (dopmas[i])
			{
				if (dop_func_exe(envl, mas, i, &dopmas) == 1)
					return (1);
				i++;
			}
			free_dmas(&dopmas);
		}
		d++;
	}
	return (0);
}

int		full_exe(char **mas, char **envl)
{
	char	*dir_name;
	char	*filename;
	int		i;
	int		d;

	i = 0;
	d = 0;
	if (find_last(mas[0], '/') != -1)
	{
		if (!(dir_name = ft_strsub(mas[0], 0, find_last(mas[0], '/')))
		|| !(filename = ft_strsub(mas[0],
			find_last(mas[0], '/') + 1, ft_strlen(mas[0]))))
			return (-1);
		i = find_exe(dir_name, filename);
		ft_strdel(&dir_name);
		ft_strdel(&filename);
		if (i == 1)
			return (do_exe(mas, envl));
		else
			return (0);
	}
	else
		return (do_search(envl, mas, i, d));
}
