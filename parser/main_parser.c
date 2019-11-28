#include "../../inc/fshell.h"

int		is_cmd_delim(int i)
{
	return (i == 1 || i == 5);
}

t_exectoken		*ft_cr_new_exectoken(t_lextoken *tmp, t_exectoken *prev, int op_type)
{
	int			d;
	int			i;
	int			dopi;
	t_lextoken	*dop;
	t_exectoken	*tmp1;

	dop = tmp;
	i = 0;
	d = 0;
	dopi = 0;
	if (tmp == NULL)
		return (NULL);
	while (tmp != NULL && tmp->operator_type == -1)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp != NULL && !is_cmd_delim(tmp->operator_type))
		i--;
	d = i;
	while (tmp != NULL && !is_cmd_delim(tmp->operator_type))
	{
		if (tmp->operator_type != -1)
			dopi++;
		tmp = tmp->next;
	}
	if (!(tmp1 = ft_memalloc(sizeof(t_exectoken))))
		return (NULL);
	if (!(tmp1->file_opt = (char**)ft_memalloc(((dopi * 3) + 1) * sizeof(char *))))
		return (NULL);
	if (!(tmp1->file_args = (char**)ft_memalloc((i + 1) * sizeof(char *))))
		return (NULL);
	tmp1->left = NULL;
	tmp1->right = NULL;
	if (prev != NULL)
	{
		if (op_type == get_op_type("|"))
			prev->left = tmp1;
		else if (op_type == get_op_type(";"))
			prev->right = tmp1;
	}
	i = 0;
	while (i < d)
	{
		if (!(tmp1->file_args[i] = ft_strsub(dop->line, 0, ft_strlen(dop->line))))
			return (NULL);
		i++;
		dop = dop->next;
	}
	tmp1->file_args[i] = NULL;
	if (dop == NULL)
		return (tmp1);
	i = 0;
	while (dop != NULL && !is_cmd_delim(dop->operator_type))
	{
		if (!(tmp1->file_opt[i] = ft_strsub(dop->line, 0, ft_strlen(dop->line))))
			return (NULL);
		i++;
		dop = dop->next;
	}
	tmp1->file_opt[i] = NULL;
	return (tmp1);
}

t_exectoken		*do_parser(t_lextoken *tmp)
{
	int			i;
	t_exectoken	*prevdot;
	t_exectoken	*prev;
	t_exectoken	*start;

	i = 0;
	if (tmp == NULL)
		return (NULL);
	if (!(prev = ft_cr_new_exectoken(tmp, NULL, -1)))
		return (NULL);
	start = prev;
	prevdot = prev;
	while (tmp != NULL && !(tmp->operator_type == 1 || tmp->operator_type == 5))
		tmp = tmp->next;
	if (tmp == NULL)
		return (start);
	while (tmp != NULL)
	{
		if (is_cmd_delim(tmp->operator_type))
			i = tmp->operator_type;
		else if (i != -1)
		{
			if (i == 5)
				if (!(prev = ft_cr_new_exectoken(tmp, prev, i)))
					return (NULL);
			if (i == 1)
			{
				if (!(prevdot = ft_cr_new_exectoken(tmp, prevdot, i)))
					return (NULL);
				prev = prevdot;
			}
			i = -1;
		}
		tmp = tmp->next;
	}
	return (start);
}


int		show_env(char **mas)
{
	int		n;

	n = 0;
	while (mas[n])
	{
		ft_printf("%s\n", mas[n]);
		n++;
	}
	return (0);
}

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_lextoken	*doptmp;
	t_exectoken	*extmp;
	t_exectoken *dopextmp;

	tmp = do_lexer(cmd);
	doptmp = tmp;
	//do_zam(tmp);
	extmp = do_parser(doptmp);
	dopextmp = extmp;
	while (extmp)
	{
		show_env(extmp->file_args);
		show_env(extmp->file_opt);
		printf("\n%p\n", extmp->right);
		printf("\n%p\n", extmp->left);
		if (extmp->right != NULL)
			extmp = extmp->right;
		else
			break ;

	}
	return (dopextmp);
}
