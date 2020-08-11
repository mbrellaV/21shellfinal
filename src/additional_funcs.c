
#include "ft_ls.h"

void		free_3ptr(DIR **ptr, struct dirent **dir, char **c, char **vptr)
{
	if (ptr && *ptr)
		closedir(*ptr);
	if (dir && *dir)
		free(*dir);
	if (c && *c)
		free(*c);
	if (vptr && *vptr)
		free(*vptr);
}

int			int_len(int number)
{
	int	count;

	count = (number == 0) ? 1 : 0;
	while (number)
	{
		count++;
		number /= 10;
	}
	return (count);
}

static void	search_max_len(t_file *struct_el, char column, int *max_len)
{
	int		len;

	len = 0;
	if (column == 'l')
		len = int_len(struct_el->nlink);
	else if (column == 'f')
		len = int_len(struct_el->file_size);
	else if (column == 'u')
		len = ft_strlen(struct_el->user_name);
	else if (column == 'g')
		len = ft_strlen(struct_el->group);
	else if (column == 'b')
		len = int_len(struct_el->st_blocks);
	else if (column == 'm')
		len = int_len(struct_el->maj);
	else if (column == 'i')
		len = int_len(struct_el->min);
	if (*max_len < len)
		*max_len = len;
}

int			max_len(t_file **struct_array, char column)
{
	int		i;
	int		max_len;

	max_len = 0;
	i = -1;
	while (struct_array[++i])
	{
		if ((!g_flags_ls->a && !g_flags_ls->f) &&
			struct_array[i]->file_name[0] == '.')
			continue ;
		else
			search_max_len(struct_array[i], column, &max_len);
	}
	return (max_len);
}

void		free_struct(t_file **files)
{
	t_file	*next_el;

	next_el = *files;
	while (next_el && next_el->next)
	{
		*files = next_el;
		free((*files)->chmod);
		free((*files)->time);
		free((*files)->date);
		free((*files)->file_name);
		next_el = (*files)->next;
		free(*files);
	}
	free(next_el->next);
	free(next_el);
}
