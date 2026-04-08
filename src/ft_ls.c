/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:26:27 by molasz-a          #+#    #+#             */
/*   Updated: 2026/04/08 16:28:55 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_ls(t_ls *data)
{
	data->path_count = 0;
	data->l_flag = 0;
	data->R_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
}

static void	read_flag(char c, t_ls *data)
{
	if (c == 'l')
		data->l_flag = 1;
	else if (c == 'R')
		data->R_flag = 1;
	else if (c == 'a')
		data->a_flag = 1;
	else if (c == 'r')
		data->r_flag = 1;
	else if (c == 't')
		data->t_flag = 1;
}

static void	read_path(char *str, t_ls *data)
{
	(void) str;
	data->path_count++;
}

static void	read_args(char **argv, t_ls *data)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			read_flag(argv[i][1], data);
		else
			read_path(argv[i], data);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_ls	data;

	init_ls(&data);
	if (argc > 1)
		read_args(argv, &data);
	return (0);
}
