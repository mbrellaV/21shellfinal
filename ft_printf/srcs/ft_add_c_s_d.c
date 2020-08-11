/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_c_s_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:30 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_width_oux(t_printf *p, char *s, int i)
{
	char		c;

	if (p->width > 0 && p->width > (int)ft_strlen(s))
	{
		c = p->zero ? '0' : ' ';
		if (*p->str == 'o' && p->accuracy > 0)
			c = ' ';
		if (p->minus == 1)
		{
			while (s[++i])
				ft_add_buff_char(p, s[i]);
			while ((int)++i <= p->width)
				ft_add_buff_char(p, c);
		}
		else if (p->minus == 0)
			ft_minus_oux(p, s, c, i);
	}
	else
		ft_add_buff_str(p, s);
}

void			ft_add_oux_help(t_printf *p, char **s, __int128_t i)
{
	char		*tmp;

	if (p->accuracy == 0 || (p->accuracy == -1 &&
			p->point == 1 && (*p->str != 'o' || i == 0)))
		ft_bzero(*s, ft_strlen(*s));
	if (p->sharp == 1 && *p->str == 'o' && (i > 0 ||
			(p->point == 1 && i == 0)))
	{
		tmp = *s;
		*s = ft_strjoin("0", tmp);
		free(tmp);
	}
}

int				ft_add_oux(t_printf *p)
{
	__int128_t	i;
	char		*s;
	char		*tmp;

	ft_take_arg_oux(p, &i);
	s = ft_str_oux(p, i);
	ft_add_oux_help(p, &s, i);
	tmp = s;
	s = ft_add_accur2(tmp, p->accuracy, p);
	free(tmp);
	if (p->sharp == 1 && (*p->str == 'X' ||
		*p->str == 'x') && i != 0 && !is_nul(s))
	{
		tmp = s;
		s = *p->str == 'x' ? ft_strjoin("0x", tmp) : ft_strjoin("0X", tmp);
		free(tmp);
	}
	ft_width_oux(p, s, -1);
	free(s);
	return (1);
}
