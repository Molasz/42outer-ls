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
	struct stat		stat;
	struct s_entry	*next;
} t_entry;

typedef struct s_dir
{
    char			*path;
    t_entry			*entries;
    struct s_dir	*next;
} t_dir;

typedef struct s_data
{
	t_dir	*dirs;

	int		l_flag;
	int		R_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
}	t_data;

int		parse_args(char **argv, t_data *data);
int		ft_diradd(t_data *data, char *path);
void	print_dirs(t_data *data);

int		ft_strcmp(char *s1, char *s2);
char	*ft_concat_path(char *s1, char *s2);

#endif
