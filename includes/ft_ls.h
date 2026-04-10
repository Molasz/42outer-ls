/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:14:04 by molasz-a          #+#    #+#             */
/*   Updated: 2026/04/10 13:05:47 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../printf/ft_printf.h"

typedef struct s_ls
{
	char	**paths;
	int		path_count;

	int		l_flag;
	int		R_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
}	t_ls;

#endif
