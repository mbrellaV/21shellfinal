/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:43:52 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:43:54 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		ft_maslen(char **mas)
{
	int i;

	i = 0;
	if (!mas)
		return (-1);
	while (mas[i])
		i++;
	return (i);
}

int		ft_maslen_with(char **mas)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!mas)
		return (-1);
	while (mas[i])
	{
		if (mas[i][0] != -128)
			len++;
		i++;
	}
	return (len);
}

int		find_last(char *line, char c)
{
	int		i;
	int		res;

	i = 0;
	res = -1;
	while (line[i])
	{
		if (line[i] == c)
			res = i;
		i++;
	}
	return (res);
}

int		do_rest(char *name, char **mas, char ***env)
{
	int tmp;

	if ((tmp = full_exe(mas, *env)) == -1)
		return (ft_error_with(8, &mas));
	else if (tmp != 1 && ft_strstr(name, "/"))
		ft_printf("minishell: file not found: %s\n", name);
	else if (tmp != 1)
		ft_printf("minishell: command not found: %s\n", name);
	return (0);
}

int		ft_dopenv(char **mas, char ***envl)
{
	if (ft_strcmp(mas[0], "setenv") == 0 && ft_maslen(mas) == 3)
		return (ft_setenv(mas, envl, *envl, 1));
	if (ft_strcmp(mas[0], "setenv") == 0 && ft_maslen(mas) != 3)
		ft_error(9);
	if (ft_strcmp(mas[0], "unsetenv") == 0 && ft_maslen(mas) == 2)
		return (ft_setenv(mas, envl, *envl, 0));
	if (ft_strcmp(mas[0], "unsetenv") == 0 && ft_maslen(mas) != 2)
		ft_error(9);
	return (0);
}
