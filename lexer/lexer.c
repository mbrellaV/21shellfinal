#include "../../inc/fshell.h"

int		ispar(char c)
{
	return (c == 34 || c == 39);
}

int			isoperator(char c)
{
	return (c == '<' || c == '&' || c == '|' || c == '>' || c == ';');
}

int			isword(char c)
{
	if (c != 34 && c != 39 && !isoperator(c) && c != ' ' && c != '\t')
		return (1);
	return (0);
}

int		c_size(char *str, char b)
{
	int i;
	int dop;

	i = 0;
	str++;
	dop = 0;
	if (*str == b)
		return (-2);
	while (*str && *str != b)
	{
		if (isword(*str) == 0 || ispar(*str))
			dop++;
		i++;
		str++;
	}
	if (*str == '\0' && dop > 0)
		return (-1);
	return (i);
}

int		operator_size(char *str)
{
	int i;

	i = 0;
	while (*str != 0 && isoperator(*str) > 0)
	{
		str++;
		i++;
	}
	return (i);
}

int		word_size(char *str)
{
	int i;

	i = 0;
	if (isoperator(*str) > 0)
		return (operator_size(str));
	if (isword(*str) == 2)
		return (c_size(str, *str));
	while (*str)
	{
		if (isword(*str) == 0)
			return (i);
		i++;
		str++;
	}
	return (i);
}


t_lextoken	*ft_cr_new_token(char *line, int word_type, int op_type)
{
	t_lextoken	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_lextoken))))
		return (NULL);
	tmp->next = NULL;
	tmp->line = line;
	tmp->word_type = word_type;
	tmp->operator_type = op_type;
	return (tmp);
}

int		get_op_type(char *operator)
{
	int i;
	static char	operators[15][5] = {";;", ";", "&&", "&", "||", "|", "<<-",\
		"<<", "<&", "<>", "<", ">>", ">&", ">|", ">"};
	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(operator, operators[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_lextoken	*add_token(t_lextoken *start, char *line, int word_type)
{
	t_lextoken	*tmp;

	if (start == NULL)
	{
		tmp = ft_cr_new_token(line, word_type, get_op_type(line));
		return (tmp);
	}
	tmp = start;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	start = tmp;
	tmp = ft_cr_new_token(line, word_type, get_op_type(line));
	start->next = tmp;
	return (tmp);
}

t_lextoken		*do_lexer(char *line)
{
	char		*tmp;
	int			dop;
	int			i;
	t_lextoken	*tail;
	t_lextoken	*doptail;

	i = 0;
	dop = 0;
	tail = NULL;
	if (line == NULL)
		return (NULL);
	if (line[0] == '\0')
		return (NULL);
	while (line[i])
	{
		if (isword(line[i]))
		{
			tmp = ft_strsub(line, i, word_size(line + i));
			tail = add_token(tail, tmp, 1);
			i += word_size(line + i);
		}
		else if (isoperator(line[i]))
		{
			tmp = ft_strsub(line, i, word_size(line + i));
			tail = add_token(tail, tmp, 0);
			i += word_size(line + i);
		}
		else
			i++;
		if (dop == 0)
			doptail = tail;
		dop++;
	}
	return (doptail);
}