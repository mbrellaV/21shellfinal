/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:38:59 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/15 16:17:33 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		ft_whatis(t_exectoken *tmp)
{
	if (ft_strcmp(tmp->file_args[0], "echo") == 0)
		ft_echo(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "cd") == 0)
		ft_cd(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "setenv") == 0)
		ft_setenv(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "unsetenv") == 0)
		ft_unsetenv(tmp->file_args);
	else if (ft_strcmp(tmp->file_args[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(tmp->file_args[0], "exit") == 0)
		return (-1);
	else if (ft_strequ(tmp->file_args[0], "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_c);
	else
		ft_infinit_pipe(tmp);
	return (1);
}

int		ft_main_norm(int flag)
{
	char	dir[4097];

	if (flag == 1)
	{
		ft_putstr_fd("quote> ", 2);
		return (ft_strlen("quote> "));
	}
	else if (flag == 0)
	{
		getcwd(dir, 4096);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd("\033[32m\044\076\033[0m ", 2);
		return (ft_strlen(dir) + 3);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("heredoc> ", 2);
		return (ft_strlen("heredoc> "));
	}
	return (0);
}

int 	ft_cheak_quote(char *input)
{
	int 	k;
	char	c;

	k = -1;
	while (input[++k])
	{
		if (input[k] == '\'' || input[k] == '\"')
		{
			c = input[k];
			while (input[++k] && input[k] != c)
				;
			if (input[k] == '\0')
				return (-1);
		}
	}
	return (1);
}

void	ft_add_intput_que(char **input, t_memory *head)
{
	char	*tmp;
	char	*t;

	t = *input;
	*input = ft_strjoinch(t, '\n');
	free(t);
	tmp = ft_read_8(ft_main_norm(1), head, 1);
	t = *input;
	*input = ft_strjoin(t, tmp);
	free(t);
	free(tmp);
	write(2, "\n", 1);
}

int		main(int argc, char **argv, char **env)
{
	char		*input;
	t_memory	*head;
	t_exectoken	*start_token;

	ft_global_env(env, argv, argc);
	ft_global_dir(0, "HOME=");
	g_cp = ft_strnew(1);
	head = ft_head_memory();
	while (1)
	{
		set_input_mode();
		atexit(reset_input_mode); //FIX IT!
		input = ft_read_8(ft_main_norm(0), head, 0);
		write(2, "\n", 1);
		while (ft_cheak_quote(input) != 1)
			ft_add_intput_que(&input, head);
		reset_input_mode();
		head = ft_memory(head, input);
		start_token = all_parse(input);
		if (ft_main_what(start_token) == -1)
			break ;
	}
	free(g_cp);
	return (0);
}
