/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:47:52 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:47:53 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		ft_error(int caseerror)
{
	if (caseerror == 15)
		ft_printf("malloc error\n");
	if (caseerror == 9)
		ft_printf("parse error\n");
	if (caseerror == 10)
		ft_printf("cant open folder");
	return (-1);
}

int		ft_error_with(int caseerror, char ***mas)
{
	if (caseerror == 15)
		ft_printf("malloc error\n");
	if (caseerror == 8)
		ft_printf("an error occured\n");
	if (caseerror == 9)
		ft_printf("parse error\n");
	if (caseerror == 10)
		ft_printf("cant open folder");
	if (caseerror == 1)
	{
		free_dmas(mas);
		return (-2);
	}
	if (caseerror == 13)
	{
		free_dmas(mas);
		return (0);
	}
	free_dmas(mas);
	return (-1);
}

int		ispar(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}
