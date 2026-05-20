/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:14:04 by molasz-a          #+#    #+#             */
/*   Updated: 2026/05/20 13:38:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../printf/ft_printf.h"
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

typedef struct s_path
{
	char			*path;
	struct stat		stat;
	struct s_path	*next;
} t_path;

typedef struct s_data
{
	t_path	*paths;

	int		l_flag;
	int		R_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
}	t_data;

int		parse_args(char **argv, t_data *data);

t_path	*ft_pathnew(char *str);
int		ft_lstadd_alpha(t_path **lst, char *str);


#endif
