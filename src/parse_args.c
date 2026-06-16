/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:22 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/16 16:30:30 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	read_flag(char *str, t_data *data)
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
			return (1);
		}
		i++;
	}
	return (0);
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
		{
			if (read_flag(argv[i] + 1, data))
				return (-1);
		}
		else
		{
			paths++;
			str = ft_strdup(argv[i]);
			if (!str || ft_diradd(data, str))
				return (-1);
		}
		i++;
	}
	return (paths);
}

int	parse_args(char **argv, t_data *data)
{
	char	*str;
	int		count;

	count = read_args(argv, data);
	if (count < 0)
		return (1);
	if (!count)
	{
		str = ft_strdup(".");
		if (!str || ft_diradd(data, str))
			return (1);
	}
	return (0);
}
