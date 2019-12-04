/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 02:59:46 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/26 02:59:47 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int 	ft_fd_flag(char **av, int *fd_in, int *p0, int *p1)
{
	int flag = 0;
	int i = -1;
	int st = 1;
	int fd;
	int b = 0;
	int f[2];

	while (av[++i])
	{
		printf("av: %s\n", av[i]);
		if (b == 0 && av[i][0] >= '0' && av[i][0] <= '9')
		{
			st = ft_atoi(av[i]);
		}
		else if ((av[i][0] == '>' || av[i][0] == '<' || av[i][0] == '&'))
		{
			ft_strcmp(av[i], ">") == 0 ? flag = 1 : flag;//Направить стандартный поток вывода в файл. Если файл не существует, он будет создан; если существует — перезаписан сверху.
			ft_strcmp(av[i], ">>") == 0 ? flag = 2 : flag;//Направить стандартный поток вывода в файл. Если файл не существует, он будет создан; если существует — данные будут дописаны к нему в конец.
			ft_strcmp(av[i], "<") == 0 ? flag = 3 : flag;//Использовать файл как источник данных для стандартного потока ввода.
			ft_strcmp(av[i], "<<") == 0 ? flag = 4 : flag;//Весь текст между блоками EOF (в общем случае вместо EOF можно использовать любое слово) будет выведен на экран. Важно: перед последним EOF не должно быть пробелов! (heredoc синтаксис).
			ft_strcmp(av[i], ">&-") == 0 ? flag = 5 : flag;//Закрыть поток вывода перед вызовом команды
			ft_strcmp(av[i], ">&") == 0 ? flag = 6 : flag;//Направить стандартный поток вывода и стандартный поток ошибок в файл. Другая форма записи: >файл 2>&1.
			ft_strcmp(av[i], "&>") == 0 ? flag = 6 : flag;
			b = 1;
		}
		else if (b == 1 && flag != 0)
		{
			if (flag == 1 || flag == 6)
				fd = open(av[i], O_CREAT | O_RDWR | O_TRUNC,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);//добавить ошибки
			else if (flag == 2)
				fd = open(av[i], O_CREAT | O_RDWR | O_APPEND,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			else if (flag == 3)
				*fd_in = open(av[i], O_RDONLY);
			if (flag == 1 || flag == 2)
			{
				dup2(fd, st);
				close(fd);
			}
			else if (flag == 6)
			{
				dup2(fd, 1);
				dup2(fd, 2);
				close(fd);
			}
			else if (flag == 5)///////////
			{
				pipe(f);
				*p0 = f[0];
				*p1 = f[1];
			}
			b = 0;
			flag = 0;
			st = 1;
		}
	}
	return (fd);
}

void    ft_infinit_pipe(t_exectoken *head)
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0;
	int		fd;

	while (head)
	{
		pipe(p);
		if ((pid = fork()) == -1)
		{
			exit(1);
		}
		else if (pid == 0)
		{
			if (head->left != NULL)///////////////////////////////
			{
				dup2(p[1], 1);
				close(p[1]);
			}
			if (head->file_opt)
				fd = ft_fd_flag(head->file_opt, &fd_in, &p[0], &p[1]);
			dup2(fd_in, 0);
			close(p[0]);
			if (ft_path_fork(head->file_args, pid) == -1)
			{
				ft_putstr_fd("21sh: command not found: ", 2);
				ft_putendl_fd(&(head->file_args[0][1]), 2);
			}
			exit(0);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0];
			head = head->left;
		}
	}
}
