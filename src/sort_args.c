
#include "ft_ls.h"
#include <errno.h>

void		sort_agrs_ascii(t_file **argv, int size, int f)
{
	int		i;
	int		j;
	int		r;
	char	*temp;

	if (size <= 1 || g_flags_ls->f)
		return ;
	r = g_flags_ls->r ? -1 * f : 1;
	i = 1;
	while (i < size)
	{
		j = i - 1;
		temp = argv[i]->file_name;
		while (j >= 0 && r * ft_strcmp(argv[j]->file_name, temp) > 0)
		{
			argv[j + 1]->file_name = argv[j]->file_name;
			j--;
		}
		argv[j + 1]->file_name = temp;
		i++;
	}
}

void		sort_agrs_size(t_file **argv, int size)
{
	int		i;
	int		j;
	int		r;
	t_file	*temp;

	r = g_flags_ls->r ? -1 : 1;
	i = 1;
	while (i < size)
	{
		j = i - 1;
		temp = argv[i];
		while (j >= 0 && r * (argv[j]->file_size - temp->file_size) < 0)
		{
			argv[j + 1] = argv[j];
			j--;
		}
		argv[j + 1] = temp;
		i++;
	}
}

void		sort_agrs_time(t_file **argv, int size)
{
	int		i;
	int		j;
	int		r;
	t_file	*temp;

	r = g_flags_ls->r ? -1 : 1;
	i = 1;
	while (i < size)
	{
		j = i - 1;
		temp = argv[i];
		while (j >= 0 && r * (argv[j]->unix_time - temp->unix_time) < 0)
		{
			argv[j + 1] = argv[j];
			j--;
		}
		argv[j + 1] = temp;
		i++;
	}
}

static int	fill_params(t_file **dirs, t_file **files, int *size_d, int size_f)
{
	int i;
	int k;

	i = -1;
	k = 0;
	while (++i < *size_d)
	{
		if (!safe_opendir(dirs[i]->file_name) && errno == ENOENT)
		{
			print_errors(&dirs[i]->file_name, 0);
			k++;
			continue ;
		}
		add_params_f(&(*(dirs)[i]), &((*(dirs[i])).file_name), NULL);
	}
	sort_agrs_ascii(dirs, *size_d, 1);
	i = -1;
	while (++i < size_f)
		add_params_f(&(*(files)[i]), &((*(files[i])).file_name), NULL);
	return (k);
}

int			sort_args(t_file **dirs, t_file **files, int *size_d, int size_f)
{
	int			k;
	extern int	errno;

	if (!g_flags_ls->f)
	{
		sort_agrs_ascii(dirs, *size_d, -1);
		sort_agrs_ascii(files, size_f, 1);
	}
	k = fill_params(dirs, files, size_d, size_f);
	if ((g_flags_ls->t || g_flags_ls->s_cap) && !g_flags_ls->f)
	{
		if (g_flags_ls->s_cap)
		{
			sort_agrs_size(dirs, *size_d);
			sort_agrs_size(files, size_f);
		}
		else
		{
			sort_agrs_time(dirs, *size_d);
			sort_agrs_time(files, size_f);
		}
	}
	return (k);
}
