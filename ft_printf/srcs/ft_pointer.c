/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:29:15 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 20:44:38 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		width_point(t_printf *p, char *s, int i)
{
	if (p->width > 0 && p->width > (int)ft_strlen(s))
	{
		if (p->minus == 1)
		{
			while (s[++i])
				ft_add_buff_char(p, s[i]);
			while (++i <= p->width)
				ft_add_buff_char(p, ' ');
		}
		else if (p->minus == 0)
		{
			while (++i < (p->width - (int)ft_strlen(s)))
				ft_add_buff_char(p, ' ');
			i = -1;
			while (s[++i])
				ft_add_buff_char(p, s[i]);
		}
	}
	else
	{
		while (s[++i])
			ft_add_buff_char(p, s[i]);
	}
}

void		accur_point(t_printf *p, char **s, int i, int sas)
{
	char	*tmp;

	if (p->accuracy > 0 && p->accuracy > (int)ft_strlen(*s))
	{
		p->accuracy -= (int)ft_strlen(*s);
		while (++i < (p->accuracy))
		{
			tmp = *s;
			*s = ft_strjoin("0", tmp);
			free(tmp);
		}
	}
	if (sas == 1)
	{
		tmp = *s;
		*s = ft_strjoin(DEC, tmp);
		free(tmp);
	}
}

int			ft_add_p(t_printf *p)
{
	void	*pointer;
	char	*s;
	int		sas;

	sas = 1;
	pointer = va_arg(p->li, void *);
	s = ft_itoa_base_c((uintmax_t)pointer, 16, -32);
	if ((p->accuracy == 0 || (p->accuracy == -1 && p->point == 1)))
		s[0] = '\0';
	if (pointer == 0x0)
	{
		sas = 0;
		ft_strdel(&s);
		s = ft_strdup("(nil)");
	}
	accur_point(p, &s, -1, sas);
	width_point(p, s, -1);
	free(s);
	return (1);
}
