/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:35 by molasz-a          #+#    #+#             */
/*   Updated: 2026/05/03 23:52:01 by molasz-a         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_ls	data;

	init_data(&data);
	if (argc > 1)
		parse_args(argv + 1, &data);
	free_data(&data);
	return (0);
}
