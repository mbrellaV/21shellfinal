/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:35 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		width_str(t_printf *p, char *s, int i)
{
	char	c;

	c = p->zero ? '0' : ' ';
	if (p->minus == 1)
	{
		while (s[++i])
			ft_add_buff_char(p, s[i]);
		while (++i <= p->width)
			ft_add_buff_char(p, c);
	}
	else if (p->minus == 0)
	{
		while (++i < (p->width - (int)ft_strlen(s)))
			ft_add_buff_char(p, c);
		i = -1;
		while (s[++i])
			ft_add_buff_char(p, s[i]);
	}
}

int			ft_addstr(t_printf *p)
{
	char	*s;
	int		i;

	i = -1;
	s = ft_strdup(va_arg(p->li, char*));
	if (s == NULL)
		s = ft_strdup("(null)");
	if ((p->accuracy > 0 || p->point == 1) && p->accuracy < (int)ft_strlen(s))
		s[p->accuracy] = '\0';
	if (p->point == 1 && p->accuracy == -1)
		s[0] = '\0';
	if (p->width > 0 && p->width > (int)ft_strlen(s))
		width_str(p, s, i);
	else
	{
		while (s[++i])
			ft_add_buff_char(p, s[i]);
	}
	free(s);
	return (1);
}
