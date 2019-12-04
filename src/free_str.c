/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 07:44:03 by mbrella           #+#    #+#             */
/*   Updated: 2019/10/30 07:44:04 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		free_dmas(char ***mas)
{
	int		i;
	char	**dopmas;

	if (!mas)
		return (0);
	i = 0;
	dopmas = *mas;
	while (dopmas[i])
	{
		ft_strdel(&dopmas[i]);
		i++;
	}
	free(*mas);
	return (0);
}
