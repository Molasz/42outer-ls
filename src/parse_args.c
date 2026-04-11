/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:22 by molasz-a          #+#    #+#             */
/*   Updated: 2026/04/11 12:36:11 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	read_flag(char *str, t_ls *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'l')
			data->l_flag = 1;
		else if (str[i] == 'R')
			data->R_flag = 1;
		else if (str[i] == 'a')
			data->a_flag = 1;
		else if (str[i] == 'r')
			data->r_flag = 1;
		else if (str[i] == 't')
			data->t_flag = 1;
		else
			return (1);
		i++;
	}
	return (0);
}

static int	read_args(char **argv, t_ls *data)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (read_flag(argv[i] + 1, data))
				return (1);
		}
		else
			data->path_count++;
		i++;
	}
	return (0);
}

static int	save_paths(char **argv, t_ls *data)
{
	int	i;
	int	j;

	data->paths = malloc((data->path_count + 1) * sizeof (t_path));
	if (!data->paths)
		return (1);
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			(data->paths + j)->path = argv[i];
			j++;
		}
		i++;
	}
	(data->paths + j)->path = NULL;
	return (0);
}

int	parse_args(char **argv, t_ls *data)
{
	if (read_args(argv, data))
		return (2);
	if (save_paths(argv, data))
		return (1);
	return (0);
}
