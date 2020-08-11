
#include "ft_ls.h"

int				check_args(char **argv, int i, t_file **dirs, t_file **files)
{
	extern int	errno;
	char		buf[512];

	if (ft_strlen(argv[i]) < 1)
		print_errors(&argv[i], 0);
	if ((!(safe_opendir(argv[i])) && errno == ENOTDIR) ||
		((readlink(argv[i], buf, 512)) > 0 &&
		(g_flags_ls->l || !safe_opendir(argv[i]))))
	{
		*files = (t_file *)ft_memalloc(sizeof(t_file));
		(*files)->file_name = argv[i];
		return (1);
	}
	*dirs = (t_file *)ft_memalloc(sizeof(t_file));
	(*dirs)->file_name = argv[i];
	return (2);
}

t_file			**sort_by_ascii(t_file **struct_array)
{
	int			i;
	int			j;
	int			r;
	t_file		*temp;

	r = g_flags_ls->r ? -1 : 1;
	i = 1;
	while (struct_array[i])
	{
		j = i - 1;
		temp = struct_array[i];
		while (j >= 0 && r * ft_strcmp(struct_array[j]->file_name,
				temp->file_name) > 0)
		{
			struct_array[j + 1] = struct_array[j];
			j--;
		}
		struct_array[j + 1] = temp;
		i++;
	}
	return (struct_array);
}

t_file			**sort_by_time(t_file **struct_array)
{
	int			i;
	int			j;
	int			r;
	t_file		*temp;

	r = g_flags_ls->r ? -1 : 1;
	i = 1;
	while (struct_array[i])
	{
		j = i - 1;
		temp = struct_array[i];
		while (j >= 0 && r * (struct_array[j]->unix_time - temp->unix_time) < 0)
		{
			struct_array[j + 1] = struct_array[j];
			j--;
		}
		struct_array[j + 1] = temp;
		i++;
	}
	return (struct_array);
}

t_file			**sort_by_size(t_file **struct_array)
{
	int			i;
	int			j;
	int			r;
	t_file		*temp;

	r = g_flags_ls->r ? -1 : 1;
	i = 1;
	while (struct_array[i])
	{
		j = i - 1;
		temp = struct_array[i];
		while (j >= 0 && r * (struct_array[j]->file_size - temp->file_size) < 0)
		{
			struct_array[j + 1] = struct_array[j];
			j--;
		}
		struct_array[j + 1] = temp;
		i++;
	}
	return (struct_array);
}
