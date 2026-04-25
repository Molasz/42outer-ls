/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:14:04 by molasz-a          #+#    #+#             */
/*   Updated: 2026/04/11 12:41:05 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../printf/ft_printf.h"

typedef struct s_path
{
	char			*path;
	struct s_path	*R_paths;
} t_path;

typedef struct s_ls
{
	t_path	*paths;
	int		path_count;

	int		l_flag;
	int		R_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
}	t_ls;

int	parse_args(char **argv, t_ls *data);

#endif
