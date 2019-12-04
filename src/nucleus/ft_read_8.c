/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:15:41 by qmartina          #+#    #+#             */
/*   Updated: 2019/11/29 17:15:43 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*ft_cut_copy(char *input, t_flag *flag, int *len, int buf)
{
	char	*tmp;

	if (buf == 25)
	{
		tmp = input;
		input = ft_strjoin_i(tmp, g_cp, flag->i, flag->max);
		flag->i += ft_strlen(g_cp);
		flag->max = ft_strlen(input);
		free(tmp);
		ft_cleanstr(flag->i + 1 + *len);
		*len = ft_main_norm(flag->mod);
		ft_putstr_fd(input, 2);
		ft_setcursor(flag->i, flag->max);
	}
	else if (buf == 23)
	{
		free(g_cp);
		g_cp = ft_strndup(input, flag->i);
		tmp = input;
		input = ft_strdup(&tmp[flag->i]);
		free(tmp);
		ft_cleanstr(flag->i + 1 + *len);
		*len = ft_main_norm(flag->mod);
		*flag = (t_flag){0, ft_strlen(input), flag->rt, flag->sum, flag->a, flag->mod};
		ft_putstr_fd(input, 2);
		ft_setcursor(0, flag->max);

	}
	else if (buf == 21)
	{
		free(g_cp);
		g_cp = ft_strdup(input);
		free(input);
		input = ft_strnew(1);
		ft_cleanstr(flag->i + 1 + *len);
		*len = ft_main_norm(flag->mod);
		*flag = (t_flag){0, 0, flag->rt, flag->sum, flag->a, flag->mod};
	}
	return (input);
}

void	ft_arrows(t_flag *flag, int len, int sum, char *input)
{
	if (sum == 297)
	{
		while (flag->i-- > 0)
			write(2, "\b", 1);
		flag->i = 0;
	}
	else if (sum == 298)
	{
		while (++flag->i <= flag->max)
		{
			if (ft_put_n(len, flag->i, flag->max) == - 1)
				tputs(tgetstr("nd", NULL), 1, ft_c);
		}
		flag->i--;
	}
	else if (sum == 190)
		ft_back_slovo(input, flag);
	else if (sum == 188)
		ft_next_slovo(input, flag, len);
}

void	ft_do_leftright(t_flag *flag, int len, int sum)/*лево вправо + история*/
{
	if (sum == 186 && flag->i > 0)
	{
		write(2, "\b", 1);
		flag->i--;
	}
	else if (sum == 185 && flag->i < flag->max)
	{
		if (ft_put_n(len, flag->i + 1, flag->max) == - 1)
			tputs(tgetstr("nd", NULL), 1, ft_c);
		flag->i++;
	}
}

void	ft_do_copy(char *input)
{
	free(g_cp);
	g_cp = ft_strdup(input);
}

char	*ft_do_addch(t_flag *flag, char *input, char buf, int *len)/*запись посимвольно в импут*/
{
	char	*tmp;

	tmp = input;
	input = ft_strjoinch_i(tmp, buf, flag->i, flag->max + 1);
	free(tmp);
	flag->i++;
	flag->max = ft_strlen(input);
	ft_cleanstr(flag->i + 1 + *len);
	*len = ft_main_norm(flag->mod);
	ft_putstr_fd(input, 2);;
	ft_setcursor(flag->i, flag->max);
	return (input);
}

char	*ft_do_delch(t_flag *flag, char *input, int *len)/*удаление*/
{
	char	*tmp;

	if (flag->i > 0)
	{
		tmp = input;
		flag->i--;
		input = ft_strdelch(tmp, flag->i, flag->max);
		free(tmp);
		flag->max = ft_strlen(input);
		ft_cleanstr(flag->i + 1 + *len);
		*len = ft_main_norm(flag->mod);
		ft_putstr_fd(input, 2);
		ft_setcursor(flag->i, flag->max);
	}
	return (input);
}

int 	ft_add_sumchar(char *str, int rt)/*складываю считанные символы для проверки на стрелки*/
{
	int i;
	int sum;

	i = -1;
	sum = 0;
	while (++i < rt)
	{
		sum += str[i];
	}
	return (sum);
}

char	*ft_read_8(int len, t_memory *head, int mod)
{
	char	*input;
	t_flag	flag;
	char	buf[8];
	t_memory *mem;

	input = ft_strnew(1);
	mem = head;
	flag = (t_flag){0, 0, 0, 0, 0, mod};
	while ((flag.rt = read(0, buf, 8)) && buf[0] != '\n')
	{
		flag.sum = ft_add_sumchar(buf, flag.rt);
		if (flag.rt > 1)
		{
			flag.sum == 186  || flag.sum == 185 ? ft_do_leftright(&flag, len, flag.sum) : NULL;
			flag.sum == 183 || flag.sum == 184 ? ft_putmemory(&mem, flag.sum, &input, &flag) : NULL;
			flag.sum == 341 ? ft_upcursor(&flag) : NULL;
			flag.sum == 342 ? ft_downcursor(&flag, len) : NULL;
			flag.sum == 297 || flag.sum == 298 || flag.sum == 190 || flag.sum == 188 ? ft_arrows(&flag, len, flag.sum, input) : NULL;
		}
		else
		{
			if (flag.sum == 25 || flag.sum == 23 || flag.sum == 21)
				input = ft_cut_copy(input, &flag, &len, flag.sum);
			else if (flag.sum == 3 || flag.sum == 4 || flag.sum == 26)
			{
				if (flag.sum == 3)
					return(input = ft_signal(3, input));
				else if (flag.sum == 4)
				{
					// ft_cleanstr(flag.i + 1 + len);//FIX IT!!!!!!!!!!!!!!!!
					// reset_input_mode();
					// return (0);
					write(1, "D", 1);
				}
				else if (flag.sum == 26)
					exit(0);//FIX IT!!!!!!!!!!!!!!!!
			}
			else if (flag.sum == 127)
				input = ft_do_delch(&flag, input, &len);
			else if (flag.sum == 27)
				flag.a = 1;
			else if (flag.sum == 119 && flag.a == 1)
			{
				ft_do_copy(input);
				flag.a = 0;
			}
			else
				input = ft_do_addch(&flag, input, buf[0], &len);
		}
		flag.sum = 0;
	}
	return (input);
}