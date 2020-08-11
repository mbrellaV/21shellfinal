/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_okr_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:03 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_okr2(char *s, t_printf *p, int i, int j)
{
	if (s[i] >= '5')
	{
		s[i] = '0';
		while (s[i - 1] && s[i - 1] == '9')
		{
			s[i - 1] = '0';
			i--;
		}
		if (s[i - 1] != '.')
			s[i - 1]++;
		else
		{
			while (s[i - 2] && s[i - 2] == '9')
			{
				s[i - 2] = '0';
				i--;
			}
			s[i - 2]++;
		}
	}
	s[j + p->accuracy] = '\0';
}

void			ft_okr(char *s, t_printf *p)
{
	int					i;
	int					j;

	if (p->accuracy == -1)
		p->accuracy = 6;
	j = -1;
	while (s[++j] && s[j] != '.')
		;
	j++;
	i = j + p->accuracy;
	ft_okr2(s, p, i, j);
	if (p->sharp == 1)
		s[j++ - 1] = '.';
	if (p->accuracy == 0)
		s[j - 1] = '\0';
}
