/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:19:16 by aolen             #+#    #+#             */
/*   Updated: 2019/10/23 19:19:22 by aolen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/sysmacros.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include "ft_printf.h"
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

typedef struct		s_flags_ls
{
	int				l;
	int				a;
	int				r_cap;
	int				r;
	int				t;
	int				g;
	int				a_cap;
	int				f;
	int				s_cap;
	int				m;
	int				s;
	int				one;
}					t_flags_ls;

t_flags_ls			*g_flags_ls;

typedef struct		s_file
{
	char			*chmod;
	int				nlink;
	char			*user_name;
	char			*group;
	char			*date;
	int				file_size;
	unsigned int	min;
	unsigned int	maj;
	char			*time;
	long			unix_time;
	char			*file_name;
	int				st_blocks;
	struct s_file	*next;
}					t_file;

struct				s_ls_vars
{
	unsigned int	total_blocks;
}					g_ls_vars;

struct				s_ls_sizes
{
	int				link_len;
	int				size_len;
	int				user_len;
	int				block_len;
	int				group_len;
	int				maj_len;
	int				minor_len;
};

int					complete_list(t_file *files, char *file_name);
t_file				**sort_by_ascii(t_file **struct_array);
void				print_ls(t_file **struct_array,
					char *dir_name, int r_flag, int f);
t_file				**sort_by_time(t_file **struct_array);
t_file				**sort_by_size(t_file **struct_array);
char				*ft_strjoin_safe(char **str1, const char *str2);
void				free_3ptr(DIR **ptr, struct dirent **dir,
					char **c, char **vptr);
char				*ft_strndup(const char *str, int n);
void				print_errors(char **filename, int r);
void				print_usage(char *argv0, char invalid_flag);
void				print_directory(char *filename, int f);
int					sort_args(t_file **dirs, t_file **files,
					int *size_d, int size_f);
t_file				*add_params_f(t_file *files, char **d_name,
					struct dirent *dir);
int					check_flags_ls(int argc, char **argv);
int					int_len(int number);
int					max_len(t_file **struct_array, char column);
void				add_major_minor(struct stat file_stat, t_file *files);
void				add_chmod(t_file *files, char *d_name, struct dirent *dir);
void				add_chmod_files(t_file *files, char *d_name);
void				free_struct(t_file **files);
int					safe_opendir(char *d_name);
int					check_args(char **argv, int i,
					t_file **dirs, t_file **files);

#endif
