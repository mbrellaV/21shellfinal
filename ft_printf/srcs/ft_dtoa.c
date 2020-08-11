/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <mbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:30:18 by mbrella           #+#    #+#             */
/*   Updated: 2020/08/08 18:40:56 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <math.h>

void			ft_exp_while(t_dtoa *t)
{
	t->c[t->i] ^= t->c[t->j];
	t->c[t->j] ^= t->c[t->i];
	t->c[t->i] ^= t->c[t->j];
	t->i++;
	t->j--;
}

void			ft_exponent(t_dtoa *t)
{
	if (t->useexp)
	{
		*(t->c++) = 'e';
		if (t->m1 > 0)
			*(t->c++) = '+';
		else
		{
			*(t->c++) = '-';
			t->m1 = -t->m1;
		}
		t->m = 0;
		while (t->m1 > 0)
		{
			*(t->c++) = '0' + t->m1 % 10;
			t->m1 /= 10;
			t->m++;
		}
		t->c -= t->m;
		t->i = 0;
		t->j = t->m - 1;
		while (t->i < t->j)
			ft_exp_while(t);
		t->c += t->m;
	}
}

void			ft_magnitude(t_dtoa *t, long double *n)
{
	if (t->neg)
		*n = -*n;
	t->m = ft_log10(*n);
	t->useexp = (t->m >= 14 || (t->neg && t->m >= 10) || t->m <= -9);
	if (t->neg)
		*(t->c++) = '-';
	if (t->useexp)
	{
		if (t->m < 0)
			t->m -= 1.0;
		*n = *n / ft_pow(10.0, t->m);
		t->m1 = t->m;
		t->m = 0;
	}
	if (t->m < 1.0)
		t->m = 0;
}

void			ft_convert_exponent(t_dtoa *t, long double *n)
{
	while (*n >= 0.0000000000000000000001 || t->m >= 0)
	{
		t->weight = ft_pow(10.0, t->m);
		if (t->weight > 0 && !isinf(t->weight))
		{
			t->digit = ft_floor(*n / t->weight);
			*n -= (t->digit * t->weight);
			*(t->c++) = '0' + t->digit;
		}
		if (t->m == 0 && *n > 0)
			*(t->c++) = '.';
		t->m--;
	}
}

char			*dtoa(char *s, long double n)
{
	t_dtoa		t;

	t.c = s;
	t.neg = (n < 0) ? 1 : 0;
	if (isnan(n))
		ft_strcpy(s, "nan");
	else if (isinf(n))
		ft_strcpy(s, "inf");
	if (n == 0.0)
		ft_strcpy(s, "0");
	else
	{
		ft_magnitude(&t, &n);
		ft_convert_exponent(&t, &n);
		ft_exponent(&t);
	}
	return (s);
}
