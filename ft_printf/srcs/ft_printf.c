/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:24:33 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 20:08:48 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf	p;

	init_printf(&p, format, 1);
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			if (ft_parser(&p) == -1)
			{
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	return (return_print(&p));
}

int				ft_dprintf(int fd, const char *format, ...)
{
	t_printf	p;

	init_printf(&p, format, fd);
	va_start(p.li, format);
	while (*p.str)
	{
		if (*p.str == '%')
		{
			if (*(++p.str) == '\0')
				break ;
			if (ft_parser(&p) == -1)
			{
				ft_add_buff(&p);
			}
		}
		else
			ft_add_buff(&p);
		p.str++;
	}
	va_end(p.li);
	return (return_print(&p));
}
