/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:41 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_add_accur(char *str, int acu, t_printf *p)
{
	char		*s;
	int			i;
	int			len;

	if (acu == -1)
		return (ft_strdup(str));
	if (!(s = (char *)ft_memalloc(sizeof(char) * acu + 2)))
		exit(1);
	len = (int)ft_strlen(str);
	i = -1;
	if (str[0] == '-')
	{
		s[++i] = '-';
		str[0] = '0';
		len--;
	}
	while (++i < (acu - len))
		s[i] = '0';
	len = -1;
	while (str[++len])
		s[i + len] = str[len];
	s[i + len] = '\0';
	free(str);
	p->zero = 0;
	return (s);
}

int				ft_add_plus(t_printf *p, int flag)
{
	if (p->buff_index != 0 && flag == 1)
		p->buff_index--;
	ft_add_buff_char(p, '+');
	return (1);
}

void			add_minus(t_printf *p, int64_t nbr, int64_t k, char *s)
{
	char		c;

	c = p->zero ? '0' : ' ';
	k += p->plus && nbr >= 0 ? ft_add_plus(p, 1) : 0;
	ft_add_buff_str(p, s);
	while (p->width - ++k)
		ft_add_buff_char(p, c);
}

void			nbr_widh(t_printf *p, int64_t nbr, int64_t k, char *s)
{
	char		c;

	if (p->width > 0 && k < p->width)
	{
		c = p->zero ? '0' : ' ';
		if (p->minus == 1)
			add_minus(p, nbr, k, s);
		else if (p->minus == 0)
		{
			p->width -= nbr < 0 && p->zero ? ft_add_buff_char(p, '-') : 0;
			s[0] = nbr < 0 && p->zero && p->width > k ? '0' : s[0];
			k += p->plus && nbr >= 0 && p->zero ? ft_add_plus(p, 0) : 0;
			while (++k < p->width)
				ft_add_buff_char(p, c);
			if (p->width == (int)ft_strlen(s) - 1)
				p->buff_index--;
			p->plus && nbr >= 0 && !p->zero ? ft_add_plus(p, 1) : 0;
			ft_add_buff_str(p, s);
		}
	}
	else
	{
		p->plus && nbr >= 0 ? ft_add_plus(p, 0) : 0;
		ft_add_buff_str(p, s);
	}
}

int				ft_addnbr(t_printf *p)
{
	int64_t		nbr;
	char		*s;
	int64_t		k;

	nbr = va_arg(p->li, long long);
	nbr = (p->l == 0) ? (int)nbr : nbr;
	nbr = (p->h == 1) ? (short)nbr : nbr;
	nbr = (p->h == 2) ? (char)nbr : nbr;
	s = ft_itoa_base_c(nbr, 10, 0);
	if (p->accuracy > (int)ft_strlen(s) ||
		(nbr < 0 && p->accuracy > (int)ft_strlen(s) - 1))
		s = ft_add_accur(s, p->accuracy, p);
	if ((p->accuracy == 0 || (p->accuracy == -1 && p->point == 1)) && nbr == 0)
		s[0] = '\0';
	k = (__int128_t)ft_strlen(s) - 1;
	p->zero = p->accuracy > 0 ? 0 : p->zero;
	if (p->space == 1 && s[0] != '-')
	{
		ft_add_buff_char(p, ' ');
		p->width--;
	}
	nbr_widh(p, nbr, k, s);
	free(s);
	return (1);
}
