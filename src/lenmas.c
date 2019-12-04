/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenmas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrella <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:35:21 by mbrella           #+#    #+#             */
/*   Updated: 2019/11/05 17:35:24 by mbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fshell.h"

int		print_path(void)
{
	char path[1024];

	getcwd(path, sizeof(path));
	ft_printf("%s\n", path);
	return (0);
}

int		dop_go_to_dir(char *line, char ***envl)
{
	char	*dopline;
	char	**splitline;
	char	path[1024];

	ft_bzero(path, sizeof(path));
	getcwd(path, sizeof(path));
	if (!(dopline = ft_strjoin("setenv OLDPWD ", path))
		|| !(splitline = ft_split_echo(dopline, " ")))
		return (-1);
	if ((full_env(splitline, envl)) == -1)
		return (-1);
	ft_strdel(&dopline);
	free_dmas(&splitline);
	return (0);
}
