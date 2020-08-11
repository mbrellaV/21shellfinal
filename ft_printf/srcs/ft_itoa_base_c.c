/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:14 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_itoa_base_c(__int128_t value, int base, int up)
{
	char		*s;
	__int128_t	n;
	int			sign;
	int			i;

	n = (value < 0) ? -value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	if (value < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	if (base == 10 && up > i)
		i += up - i;
	s = ft_strnew(i + 1);
	n = (value < 0) ? -value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base +
				('A' + (-1 * up)) - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}
