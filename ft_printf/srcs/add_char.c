/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:49 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_addchar_c(t_printf *p, char ch)
{
	int			c;
	int			i;

	i = 0;
	if (p->width > 0)
	{
		if (p->minus == 1)
			ft_add_buff_char(p, ch);
		if (p->zero == 1)
			c = '0';
		else
			c = ' ';
		while (++i < p->width)
			ft_add_buff_char(p, c);
		if (p->minus == 0)
			ft_add_buff_char(p, ch);
	}
	else
		ft_add_buff_char(p, ch);
	return (1);
}

int				ft_addchar(t_printf *p)
{
	int			c;
	int			i;

	i = 0;
	if (p->width > 0)
	{
		if (p->minus == 1)
			ft_add_buff_char(p, va_arg(p->li, int));
		if (p->zero == 1)
			c = '0';
		else
			c = ' ';
		while (++i < p->width)
			ft_add_buff_char(p, c);
		if (p->minus == 0)
			ft_add_buff_char(p, va_arg(p->li, int));
	}
	else
		ft_add_buff_char(p, va_arg(p->li, int));
	return (1);
}
