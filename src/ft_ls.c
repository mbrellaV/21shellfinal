
#include "ft_ls.h"
#define MAX_LEN 512

static t_file	**make_array(t_file *files)
{
	t_file		**struct_array;
	t_file		*start;
	int			i;

	i = 0;
	start = files;
	while (files)
	{
		i++;
		files = files->next;
	}
	struct_array = (t_file **)malloc(sizeof(*struct_array) * i);
	i = 0;
	files = start;
	while (files)
	{
		struct_array[i] = files;
		files = files->next;
		i++;
	}
	struct_array[i - 1] = NULL;
	return (struct_array);
}

static t_file	**sort_list(t_file *files)
{
	t_file **struct_array;

	struct_array = make_array(files);
	if (!g_flags_ls->f)
		sort_by_ascii(struct_array);
	if (g_flags_ls->t && !g_flags_ls->f)
		sort_by_time(struct_array);
	if (g_flags_ls->s_cap && !g_flags_ls->f)
		sort_by_size(struct_array);
	return (struct_array);
}

void			ft_ls(char *file_name, int r_flag, int k)
{
	t_file		*files;
	t_file		**struct_array;
	char		*ptr;

	files = (t_file *)ft_memalloc(sizeof(t_file));
	if (complete_list(files, file_name) < 0)
		return (print_errors(&file_name, r_flag));
	struct_array = sort_list(files);
	print_ls(struct_array, file_name, r_flag, 0);
	while (struct_array[++k] && g_flags_ls->r_cap)
		if (struct_array[k]->chmod[0] == 'd' &&
		!(ft_strequ(struct_array[k]->file_name, ".") ||
			ft_strequ(struct_array[k]->file_name, "..")))
		{
			if (!(g_flags_ls->a_cap || g_flags_ls->a) &&
			struct_array[k]->file_name[0] == '.')
				continue ;
			ptr = ft_strjoin(file_name, "/");
			ptr = ft_strjoin_safe(&ptr, struct_array[k]->file_name);
			ft_ls(ptr, 1, -1);
			ft_strdel(&ptr);
		}
	free(struct_array);
	free_struct(&files);
}

static int		handle_args(t_file **dirs, t_file **files,
				int *argc, char **argv)
{
	int			i;
	int			size_f;
	int			size_d;
	int			sizes;

	i = check_flags_ls(*argc, argv) - 1;
	size_f = 0;
	size_d = 0;
	while (++i < *argc)
		if ((sizes = check_args(argv, i, &dirs[size_d], &files[size_f])) == 1)
			size_f++;
		else if (sizes == 2)
			size_d++;
	i = sort_args(dirs, files, &size_d, size_f);
	if (size_d == 0 && size_f == 0)
		ft_ls(".", 0, -1);
	print_ls(files, NULL, 0, 1);
	if (g_flags_ls->m && size_f > 0)
		ft_printf("\n\n");
	else if (size_d - i > 0 && size_f > 0)
		ft_printf("\n");
	*argc = size_f;
	return (size_d);
}

int				main(int argc, char **argv)
{
	int				i;
	static t_file	*files[MAX_LEN] = {NULL};
	static t_file	*dirs[MAX_LEN] = {NULL};
	int				j;

	g_flags_ls = (t_flags_ls *)ft_memalloc(sizeof(t_flags_ls));
	j = handle_args(dirs, files, &argc, argv);
	i = -1;
	while (++i < j)
		if (dirs[i] && dirs[i]->file_name[0])
		{
			if (j + argc > 1)
				print_directory(dirs[i]->file_name, 0);
			ft_ls(dirs[i]->file_name, 0, -1);
			if (dirs[i + 1] && dirs[i + 1]->file_name)
				ft_printf("\n");
		}
	free(g_flags_ls);
	return (errno != 0 ? 1 : 0);
}
