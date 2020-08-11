/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmartina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:51:15 by qmartina          #+#    #+#             */
/*   Updated: 2020/08/10 19:36:40 by petruha2001      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <math.h>
# include "libft.h"

# define DEC "0x"

typedef struct			s_printf
{
	int					sharp;
	int					zero;
	int					minus;
	int					space;
	int					plus;
	int					point;
	int					width;
	int					accuracy;
	int					fd;
	int					buff_index;
	int					buff_size;
	char				*buff;
	va_list				li;
	char				*str;
	int					l;
	int					h;
	int					up_l;
}						t_printf;

typedef struct			s_dtoa
{
	int64_t				digit;
	int64_t				m;
	int64_t				m1;
	char				*c;
	int					neg;
	int					useexp;
	long double			weight;
	int					i;
	int					j;
}						t_dtoa;

int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
int						ft_sprintf(char *buffer, const char *format, ...);
int						ft_strprintf(char **str, const char *format, ...);
void					ft_realloc_q(t_printf *p);
int						ft_addchar(t_printf *p);
int						ft_addstr(t_printf *p);
int						ft_add_p(t_printf *p);
int						ft_addnbr(t_printf *p);
int						ft_add_buff(t_printf *p);
int						ft_add_buff_char(t_printf *p, char c);
int						ft_add_buff_str(t_printf *p, char *s);
int						ft_add_p(t_printf *p);
char					*ft_itoa_base_c(__int128_t n, int base, int up);
int						ft_add_oux(t_printf *p);
int						ft_add_f(t_printf *p);
int						ft_addchar_c(t_printf *p, char ch);
int						ft_parser(t_printf *p);
void					ft_reset_flags(t_printf *p);
void					ft_get_flags(t_printf *p);
int						is_a_flag(char c);
int						is_a_printf_flag(char c);
int						ft_tocnost(t_printf *p);
int						is_a_digit(char c);
int64_t					ft_floor(long double base);
long double				ft_pow(long double base, long double exp);
int64_t					ft_log10(long double base);
int						ft_add_plus(t_printf *p, int flag);
char					*ft_add_accur(char *str, int acu, t_printf *p);
char					*dtoa(char *s, long double n);
void					ft_okr(char *s, t_printf *p);
void					ft_minus_oux(t_printf *p, char *s, char c, int i);
char					*ft_str_oux(t_printf *p, __int128_t i);
void					ft_take_arg_oux(t_printf *p, __int128_t *i);
char					*ft_add_accur2(char *str, int acu, t_printf *p);
int						is_nul(char *str);
void					cheak_zvezd(t_printf *p);
int						return_print(t_printf *p);
void					init_printf(t_printf *p, const char *format, int fd);
void					cheak_zvezd(t_printf *p);

#endif
