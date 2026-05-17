/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:14:04 by molasz-a          #+#    #+#             */
/*   Updated: 2026/05/17 19:51:54 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../printf/ft_printf.h"
# include <sys/stat.h>

typedef struct s_path
{
	char			*path;
	struct stat		stat;
	struct s_path	*next;
} t_path;

typedef struct s_ls
{
	t_list	*paths;

	int		l_flag;
	int		R_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
}	t_ls;

int		parse_args(char **argv, t_ls *data);

t_path	*ft_lstnew(char *str);
void	ft_lstadd_alpha(t_list **lst, char *str);


#endif
