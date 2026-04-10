/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:26:27 by molasz-a          #+#    #+#             */
/*   Updated: 2026/04/10 13:22:21 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_ls(t_ls *data)
{
	data->paths = NULL;
	data->path_count = 0;
	data->l_flag = 0;
	data->R_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
}

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

	i = 1;
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

	data->paths = malloc((data->path_count + 1) * sizeof (char *));
	i = 1;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			data->paths[j++] = argv[i];
		i++;
	}
	data->paths[j] = NULL;
	return (0);
}

static void	ls_test(t_ls *data)
{
	int i = 0;
	while (data->paths[i])
		printf("%s\n", data->paths[i++]);

	if (data->l_flag)
		printf("l flag\n");
	if (data->R_flag)
		printf("R flag\n");
	if (data->a_flag)
		printf("a flag\n");
	if (data->r_flag)
		printf("r flag\n");
	if (data->t_flag)
		printf("t flag\n");
}

int	main(int argc, char **argv)
{
	t_ls	data;

	init_ls(&data);
	if (argc > 1)
	{
		if (read_args(argv, &data))
			return (1);
		if (save_paths(argv, &data))
			return (1);
	}

	ls_test(&data);
	return (0);
}
