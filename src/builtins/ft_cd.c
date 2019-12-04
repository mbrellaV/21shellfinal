/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:03:14 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/24 20:03:16 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_cd_error(char *tmp)
{
	if (access(tmp, 0) == -1)
		ft_putstr("cd: no such file or directory: ");
	else if (access(tmp, 3) == -1)
		ft_putstr("cd: permission denied: ");
	else
		ft_putstr("cd: not a directory: ");
	ft_putendl(tmp);
}

void	ft_global_dir(int flag, char *str)
{
	int		k;
	char	tmp[4097];

	k = ft_findenv(str);
	if (k != -404 && flag == 0)
		g_dir = ft_strdup(&g_env[k][5]);
	else if (k == -404 && flag == 0)
		g_dir = ft_strnew(1);
	else if (flag == 1)
	{
		free(g_dir);
		g_dir = ft_strdup(str);
	}
	else if (flag == 2)
	{
		getcwd(tmp, 4096);
		k = chdir(str);
		if (k == -1)
			ft_cd_error(str);
		else
		{
			free(g_dir);
			g_dir = ft_strdup(tmp);
		}
	}
}

void	ft_cd1(void)
{
	int k;

	k = ft_findenv("HOME=");
	if (k == -404)
		ft_putendl("cd: no such HOME directory");
	else
		ft_global_dir(2, &g_env[k][5]);
}

char	*ft_tmp_space(char *tmp)
{
	int		k;
	int		i;

	k = -1;
	while (tmp[++k])
	{
		if ((tmp[k] == ' ' || tmp[k] == '\t') && tmp[k - 1] != '\\')
		{
			tmp[k] = '\0';
			break ;
		}
		else if (tmp[k] == ' ' && tmp[k - 1] == '\\')
		{
			i = k;
			tmp[k - 1] = ' ';
			while (tmp[i + 1])
			{
				tmp[i] = tmp[i + 1];
				i++;
			}
			tmp[i + 1] = '\0';
		}
	}
	return (tmp);
}

void	ft_cd(char **str)
{
	char	*tmp;

	if (str[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(str[1], 2);
		return ;
	}
	if (!str[1])
		return (ft_cd1());
	if (str[1][0] == '~')
		tmp = ft_cd_home(str[1]);
	else if (str[1][0] == '-')
		return (ft_global_dir(2, g_dir));
	else
		tmp = ft_strdup(str[1]);
	// tmp = ft_tmp_space(tmp);
	ft_global_dir(2, tmp);
	free(tmp);
}
