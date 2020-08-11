/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:29:21 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			toc_width_arg(t_printf *p)
{
	p->width = va_arg(p->li, int);
	if (p->width < 0)
	{
		p->minus = 1;
		p->width *= -1;
		p->zero = 0;
	}
}

int				ft_tocnost(t_printf *p)
{
	if (p->width == -4242)
		toc_width_arg(p);
	if (p->point == 0 && *p->str >= '0' && *p->str <= '9')
	{
		p->width = ft_atoi(p->str);
		while (*p->str >= '0' && *p->str <= '9')
			p->str++;
		if (*p->str == '.')
		{
			p->str++;
			if (*p->str == '*')
				p->accuracy = -4242;
			p->point = 1;
		}
	}
	if (p->accuracy == -4242)
		p->accuracy = va_arg(p->li, int);
	else if (p->point == 1)
		p->accuracy = ft_atoi(p->str);
	while (*p->str >= '0' && *p->str <= '9')
		p->str++;
	if (*p->str == '*')
		p->str++;
	return (1);
}

int				is_a_printf_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' ||
		c == '+' || c == '.' || c == '*')
		return (1);
	return (0);
}

int				is_a_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int				is_a_flag(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == '.' || c == '%' || c == 'h' || c == 'l' ||
		c == 'j' || c == 'z' || c == 'f' || c == 'L' ||
		c == '*' || is_a_digit(c))
		return (1);
	return (0);
}
