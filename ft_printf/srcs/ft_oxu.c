/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oxu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:29:39 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:58 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_add_accur2(char *str, int acu, t_printf *p)
{
	char			*s;
	int				i;
	int				len;

	if (acu == -1 || (*p->str == 'o' && acu <= (int)ft_strlen(str)))
		return (ft_strdup(str));
	if (!(s = ft_strnew(acu + 2)))
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
	p->zero = p->accuracy > 0 ? 0 : p->zero;
	return (s);
}

int				is_nul(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '0')
			return (0);
	}
	return (1);
}

void			ft_take_arg_oux(t_printf *p, __int128_t *i)
{
	*i = va_arg(p->li, unsigned long long);
	*i = (p->l == 0) ? (unsigned)*i : *i;
	*i = (p->h == 1) ? (unsigned short)*i : *i;
	*i = (p->h == 2) ? (unsigned char)*i : *i;
}

char			*ft_str_oux(t_printf *p, __int128_t i)
{
	if (*p->str == 'o')
		return (ft_itoa_base_c(i, 8, -32));
	else if (*p->str == 'u')
		return (ft_itoa_base_c(i, 10, -32));
	else if (*p->str == 'x')
		return (ft_itoa_base_c(i, 16, -32));
	else if (*p->str == 'X')
		return (ft_itoa_base_c(i, 16, 0));
	return (NULL);
}

void			ft_minus_oux(t_printf *p, char *s, char c, int i)
{
	if (p->sharp == 1 && (*p->str == 'X' ||
			*p->str == 'x') && c == '0' && !is_nul(s))
	{
		s[1] = '0';
		if (*p->str == 'x')
			ft_add_buff_str(p, "0x");
		if (*p->str == 'X')
			ft_add_buff_str(p, "0X");
		p->width -= 2;
	}
	while ((int)++i < (p->width - (int)ft_strlen(s)))
		ft_add_buff_char(p, c);
	i = (p->buff[p->buff_index - 1] == 'x' ||
			p->buff[p->buff_index - 1] == 'X') &&
		p->sharp == 1 && c == '0' ? 0 : -1;
	while (s[++i])
		ft_add_buff_char(p, s[i]);
}
