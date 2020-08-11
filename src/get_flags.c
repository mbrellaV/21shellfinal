
#include "ft_ls.h"

static int	collect_flags_2(char flag)
{
	if (flag == 's')
		g_flags_ls->s = 1;
	else if (flag == 'f')
		g_flags_ls->f = 1;
	else if (flag == 'm')
		g_flags_ls->m = 1;
	else if (flag == 'g')
	{
		g_flags_ls->g = 1;
		g_flags_ls->one = 0;
	}
	else if (flag == '1')
	{
		g_flags_ls->one = 1;
		g_flags_ls->g = 0;
		g_flags_ls->l = 0;
	}
	else
		return (0);
	return (1);
}

static int	collect_flags(char flag)
{
	if (flag == 'l')
	{
		g_flags_ls->l = 1;
		g_flags_ls->one = 0;
	}
	else if (flag == 'R')
		g_flags_ls->r_cap = 1;
	else if (flag == 'a')
	{
		g_flags_ls->a = 1;
		g_flags_ls->a_cap = 0;
	}
	else if (flag == 'r')
		g_flags_ls->r = 1;
	else if (flag == 't')
		g_flags_ls->t = 1;
	else if (flag == 'A')
		g_flags_ls->a_cap = g_flags_ls->a ? 0 : 1;
	else if (flag == 'S')
		g_flags_ls->s_cap = 1;
	else
		return (collect_flags_2(flag));
	return (1);
}

int			check_flags_ls(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' && argv[i][j + 1] != 0)
		{
			while (argv[i][++j])
			{
				if (collect_flags(argv[i][j]))
					continue ;
				else if (argv[i][j] == '-' && j == 1 && argv[i][j + 1] == '\0')
					return (i + 1);
				else
					print_usage(argv[0], argv[i][j]);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}
