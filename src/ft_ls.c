/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:40:06 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/29 00:40:07 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_data(t_data *data)
{
	data->dirs = NULL;
	data->files = NULL;
	data->l_flag = 0;
	data->rec_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
	data->exit_code = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	init_data(&data);
	parse_args(argv + 1, &data);
	print_data(&data);
	free_exit(&data, data.exit_code);
	return (0);
}
