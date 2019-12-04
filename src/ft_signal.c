/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:13:27 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/04 17:13:30 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

void	ft_fork_signal(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, ft_fork_signal);
		// exit(EXIT_SUCCESS);
	}
	else if (signo == SIGTSTP)
	{
		// kill(getpid(), SIGTSTP);
		// ft_putstr("\n");
		// // signal(SIGTSTP, ft_fork_signal);
		// signal(SIGSTOP, SIG_DFL);
		ft_putendl("its work");
	}
	else if (signo == SIGCONT)
		signal(SIGCONT, ft_fork_signal);
}

char	*ft_signal(int signo, char *input)
{
	if (signo == 3)
	{
		// ft_putstr("\n");
		// ft_main_norm("", 0, NULL);
		free(input);
		input = ft_strnew(1);
		return (input);
	}
	return (NULL);
}

int		ft_main_what(t_exectoken *tmp)
{
	int		i;

	i = -1;
	while (tmp)
	{
		if (ft_whatis(tmp) == -1)
			return (-1);
		tmp = tmp->right;
	}
	return (1);
}
