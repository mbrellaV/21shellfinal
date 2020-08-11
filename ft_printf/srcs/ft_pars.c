/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:29:31 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_get_flags(t_printf *p)
{
	while (is_a_printf_flag(*p->str))
	{
		if (*p->str == '#')
			p->sharp = 1;
		else if (*p->str == '0' && *(p->str + 1) != '.')
			p->zero = 1;
		else if (*p->str == '-')
			p->minus = 1;
		else if (*p->str == ' ')
			p->space = 1;
		else if (*p->str == '+')
			p->plus = 1;
		else if (*p->str == '*')
			p->width = -4242;
		else if (*p->str == '.')
		{
			p->zero = 0;
			p->point = 1;
			p->str++;
			cheak_zvezd(p);
			break ;
		}
		p->str++;
	}
}

void			ft_reset_flags(t_printf *p)
{
	p->sharp = 0;
	p->zero = 0;
	p->minus = 0;
	p->space = 0;
	p->plus = 0;
	p->point = 0;
	p->width = 0;
	p->accuracy = -1;
	p->l = 0;
	p->h = 0;
	p->up_l = 0;
}

void			ft_check_lh_big_l(t_printf *p)
{
	while (*p->str == 'l' || *p->str == 'h' || *p->str == 'L')
	{
		if (*p->str == 'l')
			p->l++;
		else if (*p->str == 'h')
			p->h++;
		else if (*p->str == 'L')
			p->up_l++;
		p->str++;
	}
}

int				check_parser(t_printf *p)
{
	if (*p->str == 's')
		ft_addstr(p);
	else if (*p->str == 'c')
		ft_addchar(p);
	else if (*p->str == '%' && *(p->str - 1) == '%')
		ft_addchar_c(p, '%');
	else if (*p->str == 'd' || *p->str == 'i')
		ft_addnbr(p);
	else if (*p->str == 'f')
		ft_add_f(p);
	else if (*p->str == 'p')
		ft_add_p(p);
	else if (*p->str == 'o' || *p->str == 'x' ||
				*p->str == 'X' || *p->str == 'u')
		ft_add_oux(p);
	else
		return (-1);
	return (1);
}

int				ft_parser(t_printf *p)
{
	ft_reset_flags(p);
	ft_get_flags(p);
	if (!is_a_flag(*p->str))
	{
		return (-1);
	}
	p->space = (p->plus == 1 && p->space == 1) ? 0 : p->space;
	p->zero = (p->zero == 1 && p->minus == 1) ? 0 : p->zero;
	if (is_a_digit(*p->str) || p->accuracy == -4242 || p->width == -4242)
		ft_tocnost(p);
	ft_check_lh_big_l(p);
	return (check_parser(p));
}
