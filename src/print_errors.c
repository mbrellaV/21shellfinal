
#include "ft_ls.h"
#include <stdio.h>
#include <errno.h>

void	print_errors(char **filename, int r)
{
	char		*tmp;
	extern int	errno;

	tmp = *filename;
	if (g_flags_ls->r_cap && r)
		while (ft_strchr(tmp, '/'))
			tmp = ft_strchr(tmp, '/') + 1;
	if (errno == EACCES)
		print_directory(*filename, 1);
	ft_putstr_fd("ls: ", 2);
	if (ft_strlen(tmp) < 1)
	{
		ft_putstr_fd("fts_open", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	ft_putstr_fd(tmp, 2);
	if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", 2);
	*filename = "";
}

void	print_usage(char *argv0, char invalid_flag)
{
	ft_putstr_fd(argv0, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(invalid_flag, 2);
	ft_putstr_fd("\n", 2);
	ft_putendl_fd("usage: ls [-ARSafglmrst1] [file ...]", 2);
	exit(1);
}

void	print_directory(char *filename, int f)
{
	if (f)
		ft_printf("\n%s:\n", filename);
	else
		ft_printf("%s:\n", filename);
}
