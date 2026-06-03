/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:35 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/03 15:36:54 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_data(t_data *data)
{
	data->paths = NULL;
	data->l_flag = 0;
	data->R_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
}

static void	free_data(t_data *data)
{
	t_path	*path;
	t_path	*tmp;

	if (data->paths)
	{
		path = data->paths;
		while (path)
		{
			tmp = path->next;
			free(path);
			path = tmp;
		}
	}
}

static void	debug_paths(t_path *path)
{
	ft_printf(" --- PATHS ---\n\n");
	while (path)
	{
		ft_printf("%s\n", path->path);
		path = path->next;
	}
}

static void	debug_flags(t_data *data)
{
	ft_printf(" --- FLAGS ---\n\n");
	ft_printf("-l: %d\n", data->l_flag);
	ft_printf("-R: %d\n", data->R_flag);
	ft_printf("-a: %d\n", data->a_flag);
	ft_printf("-r: %d\n", data->r_flag);
	ft_printf("-t: %d\n", data->t_flag);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	init_data(&data);
	parse_args(argv + 1, &data);
	debug_paths(data.paths);
	debug_flags(&data);
	free_data(&data);
	return (0);
}
