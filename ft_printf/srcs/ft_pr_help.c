/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pr_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:28:53 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			cheak_zvezd(t_printf *p)
{
	if (*p->str == '*')
	{
		p->accuracy = -4242;
		p->str++;
	}
}

void			init_printf(t_printf *p, const char *format, int fd)
{
	if (format == NULL)
		exit(1);
	p->fd = fd;
	p->buff_size = 64;
	if (!(p->buff = ft_strnew(p->buff_size)))
		exit(1);
	p->buff_index = 0;
	p->str = (char *)format;
}

int				nothing(int sas)
{
	sas += 1;
	return (sas);
}

int				return_print(t_printf *p)
{
	int def;

	def = write(p->fd, p->buff, p->buff_index);
	nothing(def);
	free(p->buff);
	return (p->buff_index);
}
