/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:40:16 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/29 00:40:17 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	read_flag(char *str, t_data *data)
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
		{
			ft_printf("ft_ls: invalid option -- '%c'\n", str[i]);
			free_exit(data, 1);
		}
		i++;
	}
}

static int	read_args(char **argv, t_data *data)
{
	int		i;
	int		paths;
	char	*str;

	i = 0;
	paths = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			read_flag(argv[i] + 1, data);
		else
		{
			paths++;
			str = ft_strdup(argv[i]);
			if (!str)
				free_exit(data, 1);
			diradd(data, str);
		}
		i++;
	}
	return (paths);
}

void	parse_args(char **argv, t_data *data)
{
	char	*str;

	if (!read_args(argv, data))
	{
		str = ft_strdup(".");
		if (!str)
			free_exit(data, 1);
		diradd(data, str);
	}
}
