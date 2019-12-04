/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:04:19 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/30 14:04:21 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	exit_shell(void)
{
	ft_free_str(g_env);
	write(1, "\n", 1);
	exit(0);
}

int		ft_env_len(char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (env[++i])
		count++;
	return (count);
}

void	ft_global_env(char **env, char **argv, int argc)
{
	int		i;
	int		k;
	char	*str;

	i = -1;
	k = argc;
	str = argv[0];
	g_env = (char **)ft_memalloc(sizeof(char *) * (ft_env_len(env) + 1));
	while (env[++i])
	{
		if (!(g_env[i] = ft_strdup(env[i])))
			exit_shell();
		k++;
	}
}
