/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:28:48 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/29 17:28:50 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_env(void)
{
	int i;

	i = -1;
	while (g_env[++i])
		ft_putendl(g_env[i]);
}

void	ft_setenv2(char **str, int i)
{
	if (i != -404)
	{
		free(g_env[i]);
		g_env[i] = ft_strjoin(str[1], str[2]);
	}
	else
	{
		i = 0;
		while (g_env[i])
			i++;
		g_env[i] = ft_strjoin(str[1], str[2]);
	}
}

int		ft_setenv(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 3)
		ft_putstr("setenv: Too few arguments\n");
	else if (i > 3)
		ft_putstr("setenv: Too many arguments\n");
	else
	{
		tmp = str[1];
		str[1] = ft_strjoinch(tmp, '=');
		free(tmp);
		i = ft_findenv(str[1]);
		ft_setenv2(str, i);
	}
	return (1);
}

void	ft_unsetenv2(int i)
{
	int		k;

	free(g_env[i]);
	g_env[i] = NULL;
	k = i;
	while (g_env[k + 1])
	{
		g_env[k] = ft_strdup(g_env[k + 1]);
		free(g_env[k + 1]);
		g_env[k + 1] = NULL;
		k++;
	}
}

int		ft_unsetenv(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 2)
		ft_putstr("setenv: Too few arguments\n");
	else if (i > 2)
		ft_putstr("setenv: Too many arguments\n");
	else
	{
		tmp = str[1];
		str[1] = ft_strjoinch(tmp, '=');
		free(tmp);
		i = ft_findenv(str[1]);
		if (i != -404)
			ft_unsetenv2(i);
		else
			return (-1);
	}
	return (1);
}
