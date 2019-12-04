/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nucleus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:29:27 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/25 17:29:29 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

int	ft_c(int c)
{
	write(2, &c, 1);
	return (1);
}

void	reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &saved_attributes);
}

void set_input_mode(void)
{
	struct termios tattr;

	if (!isatty(0)) /* проверяем, что вводим с терминала */
	{
		fprintf(stderr, "Not a terminal.\n");//////////////////////////////////////////////////////
		exit (1);
	}
	if (tgetent(NULL, getenv("TERM")) < 1)
		return ;
	if (tcgetattr(0, &saved_attributes) == -1)
		return ; /* считываем текущий режим работы терминала */
	memcpy(&tattr, &saved_attributes, sizeof(tattr));
	tattr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON | ISIG | IEXTEN); /* включаем неканонический режим без эха */
	tattr.c_cc[VMIN] = 1; /* считываем минимум по одному символу */
	tattr.c_cc[VTIME] = 0; /* без ограничения времени ожидания */
	if (tcsetattr(0, 0, &tattr) == -1)
		return ; /* устанавливаем новый режим работы терминала */
}

int	ft_put_n(int len, int i, int max)
{
	struct winsize wins;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return (-1);
	if ((len + i) == wins.ws_col && i != max)
	{
		write(2, "\n", 1);
		return (1);
	}
	else
	{
		if (((len + i - wins.ws_col) % wins.ws_col) == 0 && i != max)
		{
			write(2, "\n", 1);
			return (1);
		}
	}
	return (-1);
}

t_memory	*ft_head_memory(void)
{
	t_memory	*head;

	head = (t_memory *)malloc(sizeof(t_memory));
	head->inp = NULL;
	head->next = NULL;
	head->back = NULL;
	return (head);
}

t_memory	*ft_memory(t_memory *back, char *str)
{
	t_memory *tmp;
	t_memory *p;

	tmp = (t_memory *)malloc(sizeof(t_memory));
	if (!tmp)
		return (NULL);
	p = back->next; //сохранение указателя на следующий узел
	back->next = tmp; // предыдущий узел указывает на создаваемый
	tmp->inp = ft_strdup(str);// сохранение поля данных добавляемого узла
	tmp->next = p; // созданный узел указывает на следующий узел
	tmp->back = back; // созданный узел указывает на предыдущий узел
	if (p != NULL)
		p->back = tmp;
	return (tmp);
}

void		ft_cleanstr(int i)
{
	while (i > 0)
	{
		write(2, "\b", 1);
		i--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_c);
}

void	ft_putmemory(t_memory **q, int sum, char **input, t_flag *flag)
{
	if (sum == 183)
	{
		if ((*q)->back && *q)
		{
			free(*input);
			*input = ft_strdup((*q)->inp);
			ft_cleanstr(flag->i);
			flag->i = ft_strlen(*input);
			flag->max = ft_strlen(*input);
			ft_putstr_fd((*q)->inp, 2);
			*q = (*q)->back;
		}
	}
	else if (sum == 184)
	{
		if ((*q)->next && *q)
		{
			*q = (*q)->next;
			free(*input);
			*input = ft_strdup((*q)->inp);
			ft_cleanstr(flag->i);
			flag->i = ft_strlen(*input);
			flag->max = ft_strlen(*input);
			ft_putstr_fd((*q)->inp, 2);
			// q = q->next;
		}
	}
}

void	ft_setcursor(int i, int max)
{
	while (max > i)
	{
		write(2, "\b", 1);
		max--;
	}
}

char *ft_strdelch(char *str, int i, int max)
{
	char	*new;
	int 	k;

	k = -1;
	new = (char *)malloc(sizeof(char) * max);
	while (++k < i)
		new[k] = str[k];
	while (str[k + 1])
	{
		new[k] = str[k + 1];
		k++;
	}
	new[k] = '\0';
	return (new);
}

void	ft_back_slovo(char *input, t_flag *flag)
{
	if (input[flag->i] == ' ')
	{
		flag->i--;
		write(2, "\b", 1);
	}
	while (input[flag->i] == ' ' && flag->i > 0)
	{
		flag->i--;
		write(2, "\b", 1);
	}
	while (input[flag->i] != ' ' && flag->i > 0)
	{
		flag->i--;
		write(2, "\b", 1);
	}
	while (input[flag->i] == ' ' && flag->i > 0)
	{
		flag->i--;
		write(2, "\b", 1);
	}
	if (flag->i != 0)
	{
		tputs(tgetstr("nd", NULL), 1, ft_c);
		flag->i++;
	}
}

void	ft_next_slovo(char *input, t_flag *flag, int len)
{
	if (input[flag->i] == ' ')
	{
		flag->i++;
		if (ft_put_n(len, flag->i, flag->max) == - 1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
	while (input[flag->i] == ' ' && flag->i < flag->max)
	{
		flag->i++;
		if (ft_put_n(len, flag->i, flag->max) == - 1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
	while (input[flag->i] != ' ' && flag->i < flag->max)
	{
		flag->i++;
		if (ft_put_n(len, flag->i, flag->max) == - 1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
	}
}

void	ft_upcursor(t_flag *flag)
{
	struct winsize wins;
	int i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	if (flag->i <= wins.ws_col)
	{
		while (flag->i-- > 0)
			write(2, "\b", 1);
		flag->i = 0;
	}
	else
	{
		i = flag->i - wins.ws_col;
		while (flag->i-- > i)
			write(2, "\b", 1);
		flag->i++;
	}
}

void	ft_downcursor(t_flag *flag, int len)
{
	struct winsize wins;
	int i;

	if (ioctl(2, TIOCGWINSZ, &wins) == -1)
		return ;
	if ((flag->max - flag->i) > wins.ws_col)
	{
		i = -1;
		while (++i < wins.ws_col)
		{
			if (ft_put_n(len, flag->i + 1, flag->max) == - 1)
				tputs(tgetstr("nd", NULL), 1, ft_c);
			flag->i++;
		}
	}
	else
	{
		while (flag->i < flag->max)
		{
			if (ft_put_n(len, flag->i + 1, flag->max) == - 1)
				tputs(tgetstr("nd", NULL), 1, ft_c);
			flag->i++;
		}
	}
}
