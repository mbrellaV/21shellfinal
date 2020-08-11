/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:24 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				is_one(char *str, long double f)
{
	int64_t				i;
	int64_t				j;

	if (f - (int64_t)f == 0)
	{
		i = (int64_t)f;
		j = 1;
		while (i /= 10)
			j++;
		if (f < 0.0)
			j++;
		str[j] = '.';
	}
	i = 0;
	while (++i < 3999)
	{
		if (str[i] != '0')
			return (0);
	}
	str[1] = '.';
	return (1);
}

void			ft_cheak_float(char *str, int64_t nbr)
{
	char				*s;
	int					i;
	int					j;

	s = ft_itoa_base_c(nbr, 10, 0);
	j = -1;
	i = 0;
	if (str[i] == '-' && s[i] != '-')
		i++;
	while (s[++j])
		str[j + i] = s[j];
	str[j + i] = '.';
	free(s);
}

void			ft_minus_f(t_printf *p, int k, char *s, long double f)
{
	char				c;

	c = p->zero ? '0' : ' ';
	k += p->plus && f >= 0.0 ? ft_add_plus(p, 1) : 0;
	ft_add_buff_str(p, s);
	while ((p->width - ++k) > 0)
		ft_add_buff_char(p, c);
}

void			ft_width_f(t_printf *p, int k, char *s, long double f)
{
	char				c;

	if (p->width > 0 && k < p->width)
	{
		c = p->zero ? '0' : ' ';
		if (p->minus == 1)
			ft_minus_f(p, k, s, f);
		else if (p->minus == 0)
		{
			p->width -= f < 0.0 && p->zero ? ft_add_buff_char(p, '-') : 0;
			s[0] = f < 0.0 && p->zero && p->width > k ? '0' : s[0];
			k += p->plus && f >= 0.0 && p->zero ? ft_add_plus(p, 1) : 0;
			while (++k < p->width)
				ft_add_buff_char(p, c);
			if (p->width == (int)ft_strlen(s) - 1)
				p->buff_index--;
			p->plus && f >= 0.0 && !p->zero ? ft_add_plus(p, 1) : 0;
			ft_add_buff_str(p, s);
		}
	}
	else
	{
		p->plus && f >= 0.0 ? ft_add_plus(p, 0) : 0;
		ft_add_buff_str(p, s);
	}
}

int				ft_add_f(t_printf *p)
{
	long double			f;
	char				s[4000];
	int					k;

	k = -1;
	while (++k < 3999)
		s[k] = '0';
	s[k] = '\0';
	if (p->up_l == 1)
		f = va_arg(p->li, long double);
	else
		f = va_arg(p->li, double);
	dtoa(s, f);
	ft_cheak_float(s, (int64_t)f);
	is_one(s, f);
	ft_okr(s, p);
	k = ft_strlen(s);
	if (p->zero == 1)
		p->minus = 0;
	if (p->space == 1 && (f >= 0.0))
		ft_add_buff_char(p, ' ');
	else
		p->width++;
	ft_width_f(p, k, s, f);
	return (1);
}
