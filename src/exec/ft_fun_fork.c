/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fun_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:04:16 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/30 19:04:17 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

void	ft_fun_fork(char *path, char **arg, pid_t pid)
{
	// pid_t	pid;

	// pid = fork();
	signal(SIGINT, ft_fork_signal);
	signal(SIGTSTP, ft_fork_signal);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	if (pid == 0)
		execve(path, arg, g_env);
	else if (pid < 0)
	{
		free(path);
		ft_putendl("Fork failed to create a new process.");
		return ;
	}
	// wait(&pid);
	if (path)
		free(path);
}

int		ft_path_while(char **path, char **argum, pid_t pid)
{
	int			k;
	struct stat mystat;
	char		*tmp;

	k = -1;
	while (path[++k])
	{
		tmp = ft_strjoin(path[k], argum[0]);
		if (lstat(tmp, &mystat) != -1)
		{
			if (mystat.st_mode & S_IXUSR)
			{
				ft_fun_fork(ft_strdup(tmp), argum, pid);
				ft_free_str(path);
				free(tmp);
				return (1);
			}
			ft_putstr("21sh: permission denied: ");
			ft_putendl(tmp);
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int		ft_fun_lstat(struct stat mystat, char **argum, pid_t pid)
{
	if (mystat.st_mode & S_IXUSR)
	{
		ft_fun_fork(ft_strdup(argum[0]), argum, pid);
		return (1);
	}
	ft_putstr("21sh: permission denied: ");
	ft_putendl(argum[0]);
	return (1);
}

int		ft_path_fork(char **argum, pid_t pid)
{
	char		**path;
	char		*tmp;	
	struct stat mystat;

	if (lstat(argum[0], &mystat) != -1)
		return (ft_fun_lstat(mystat, argum, pid));
	else
	{
		if (ft_findenv("PATH=") == -404)
			return (-1);
		path = ft_strsplit(&g_env[ft_findenv("PATH=")][5], ':');
		tmp = argum[0];
		argum[0] = ft_strjoin("/", tmp);
		free(tmp);
		if (ft_path_while(path, argum, pid) == 1)
			return (1);
		ft_free_str(path);
	}
	return (-1);
}
