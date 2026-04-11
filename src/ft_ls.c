/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:35 by molasz-a          #+#    #+#             */
/*   Updated: 2026/04/11 12:54:18 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_data(t_ls *data)
{
	data->paths = NULL;
	data->path_count = 0;
	data->l_flag = 0;
	data->R_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
}

static void	free_data(t_ls *data)
{
	int	i;

	i = 0;
	if (data->paths)
	{
		while (data->paths + i)
		{
			i++;
		}
		free(data->paths);
	}
}

static void	ls_test(t_ls data)
{
	int i = 0;

	while (data.paths && data.paths[i].path)
		ft_printf("%s\n", data.paths[i++].path);
	if (data.l_flag)
		ft_printf("l flag\n");
	if (data.R_flag)
		ft_printf("R flag\n");
	if (data.a_flag)
		ft_printf("a flag\n");
	if (data.r_flag)
		ft_printf("r flag\n");
	if (data.t_flag)
		ft_printf("t flag\n");
}

int	main(int argc, char **argv)
{
	t_ls	data;

	init_data(&data);
	if (argc > 1)
		parse_args(argv + 1, &data);
	ls_test(data);
	free_data(&data);
	return (0);
}
