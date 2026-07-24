/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:14:04 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/17 16:29:17 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../printf/ft_printf.h"
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct s_entry
{
	char			*name;
	char			*symlink;
	struct stat		stat;
	struct s_entry	*next;
}	t_entry;

typedef struct s_dir
{
	char			*path;
	t_entry			*entries;
	struct stat		stat;
	struct s_dir	*next;
}	t_dir;

typedef struct s_data
{
	t_dir	*dirs;
	t_entry	*files;

	int		l_flag;
	int		rec_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
	int		exit_code;
}	t_data;

// free
void	free_exit(t_data *data, int exitCode);
void	print_errno(t_data *data, char *err, char *path);
void	free_dirs(t_dir *dirs);

// parse_args
void	parse_args(char **argv, t_data *data);

// dir
void	add_dir(t_data *data, char *path);
t_dir	*new_dir(char *path, struct stat *st);
void	dir_enqueue(t_data *data, t_dir *dir);
t_dir	*read_subdir(t_data *data, char *path);

// entry
void	add_entry(t_data *data, t_entry **entries, char *name, char *full_path);

// print
void	print_data(t_data *data);
void	print_normal(t_entry *entry);
void	print_list(t_entry *entry);
void	print_total(t_entry *entries);

// utils
int		ft_strcmp(char *s1, char *s2);
char	*ft_concat_path(char *s1, char *s2);
char	*ft_ternary(int con, char *a, char *b);
char	*symlink_target(char *path, struct stat *st);

#endif
