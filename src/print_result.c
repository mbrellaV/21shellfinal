
#include "ft_ls.h"
#include <stdio.h>

struct s_ls_sizes g_ls_sizes;

static void	find_max(t_file **struct_array)
{
	g_ls_sizes.link_len = max_len(struct_array, 'l');
	g_ls_sizes.size_len = max_len(struct_array, 'f');
	g_ls_sizes.user_len = max_len(struct_array, 'u');
	g_ls_sizes.block_len = max_len(struct_array, 'b');
	g_ls_sizes.group_len = max_len(struct_array, 'g');
	g_ls_sizes.maj_len = max_len(struct_array, 'm');
	g_ls_sizes.minor_len = max_len(struct_array, 'i');
}

static int	check_big_a_flag(t_file *struct_el)
{
	if (g_flags_ls->a_cap && struct_el->chmod[0] == 'd' &&
	(!ft_strcmp((const char *)struct_el->file_name, ".")
	|| !ft_strcmp((const char *)struct_el->file_name, "..")))
		return (1);
	return (0);
}

static void	print_l(t_file *struct_el)
{
	if ((g_flags_ls->l && !g_flags_ls->m) ||
		(g_flags_ls->g && !g_flags_ls->m))
	{
		if (g_flags_ls->s)
			ft_printf("%*d ", g_ls_sizes.block_len, struct_el->st_blocks);
		ft_printf("%-12s", struct_el->chmod);
		ft_printf("%*d ", g_ls_sizes.link_len, struct_el->nlink);
		if (!(g_flags_ls->g))
			ft_printf("%-*s  ", g_ls_sizes.user_len, struct_el->user_name);
		ft_printf("%-*s  ", g_ls_sizes.group_len, struct_el->group);
		if (struct_el->chmod[0] != 'c' && struct_el->chmod[0] != 'b')
			ft_printf("%*d ", g_ls_sizes.size_len, struct_el->file_size);
		else
			ft_printf("%*d, %*d ", g_ls_sizes.maj_len + 1,
				struct_el->maj, g_ls_sizes.minor_len, struct_el->min);
		ft_printf("%s", struct_el->date);
		ft_printf("%5s ", struct_el->time);
	}
}

void		print_ls(t_file **struct_array, char *dir_name, int r_flag, int f)
{
	int i;

	i = -1;
	find_max(struct_array);
	if (g_ls_sizes.maj_len + g_ls_sizes.minor_len + 2 > g_ls_sizes.size_len &&
			g_ls_sizes.maj_len + g_ls_sizes.minor_len != 2)
		g_ls_sizes.size_len = g_ls_sizes.maj_len + g_ls_sizes.minor_len + 3;
	if (r_flag)
		ft_printf("\n%s:\n", dir_name);
	if ((g_flags_ls->l || g_flags_ls->g)
		&& !f && (struct_array[i + 3] || g_flags_ls->a))
		ft_printf("total %d\n", g_ls_vars.total_blocks);
	while (struct_array[++i])
	{
		if (!g_flags_ls->a && !g_flags_ls->f && !g_flags_ls->a_cap &&
		struct_array[i]->file_name[0] == '.')
			continue ;
		if (check_big_a_flag(struct_array[i]))
			continue ;
		print_l(struct_array[i]);
		if (g_flags_ls->m && (struct_array[i + 1] || f))
			ft_printf("%s, ", struct_array[i]->file_name);
		else
			ft_printf("%s\n", struct_array[i]->file_name);
	}
}
