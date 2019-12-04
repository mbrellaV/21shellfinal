/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:19:37 by qmartina          #+#    #+#             */
/*   Updated: 2019/10/24 19:19:40 by qmartina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fshell.h"

char	*ft_print_oct(char *str, int nb)
{
	while (nb > 777)
		nb /= 10;
	nb = ft_itoa_base(nb, 8);
	ft_putchar(nb);
	if (*(str + 4) >= '0' && *(str + 4) <= '9')
		str = str + 5;
	else if (*(str + 3) >= '0' && *(str + 3) <= '9')
		str = str + 4;
	return (str);
}

char	*ft_slash(char *str)
{
	int		nb;
	char	*tmp;

	tmp = str + 1;
	nb = -404;
	*(str + 1) == '\\' ? ft_putchar('\\') : NULL;
	*(str + 1) == 'a' ? ft_putchar('\a') : NULL;
	*(str + 1) == 'b' ? ft_putchar('\b') : NULL;
	*(str + 1) == 'n' ? ft_putchar('\n') : NULL;
	*(str + 1) == 'v' ? ft_putchar('\v') : NULL;
	*(str + 1) == 'r' ? ft_putchar('\r') : NULL;
	*(str + 1) == 'f' ? ft_putchar('\f') : NULL;
	*(str + 1) == '\"' ? ft_putchar('\"') : NULL;
	*(str + 1) == '\'' ? ft_putchar('\'') : NULL;
	*(str + 1) == '0' ? (nb = ft_atoi((str + 1))) : -1;
	*(str + 1) == 'x' ? (str = ft_hex(str + 1)) : str;
	if (nb >= 0)
		str = ft_print_oct(str, nb);
	if (*tmp != '\\' && *tmp != 'a' && *tmp != 'b' && *tmp != 'n'
		&& *tmp != 'v' && *tmp != 'r' && *tmp != 'f' && *tmp != '\"'
		&& *tmp != '\'' && *tmp != '0' && *tmp != 'x')
		ft_putchar('\\');
	return (str);
}

void	ft_echo(char **str)
{
	int		k;
	int		i;

	k = 0;
	while (str[++k])
	{
		i = -1;
		while (*str[k])
		{
			if (*str[k] == '\\')
				str[k] = ft_slash(str[k]);
			if (*str[k] == '$')
				str[k] = ft_put_env(str[k]);
			else
				*str[k] != '\"' ? ft_putchar(*str[k]) : NULL;
			str[k]++;
		}
	}
	ft_putchar('\n');
}
