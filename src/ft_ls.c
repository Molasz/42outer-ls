/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:35 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/16 16:31:56 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_data(t_data *data)
{
	data->dirs = NULL;
	data->dirs_tail = NULL;
	data->l_flag = 0;
	data->R_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
}

static void	free_entries(t_entry *entry)
{
	t_entry	*tmp;

	while (entry)
	{
		tmp = entry->next;
		free(entry->name);
		free(entry);
		entry = tmp;
	}
}

static void	free_dirs(t_dir *dirs)
{
	t_dir	*dir;
	t_dir	*tmp;

	dir = dirs;
	while (dir)
	{
		tmp = dir->next;
		free(dir->path);
		free_entries(dir->entries);
		free(dir);
		dir = tmp;
	}
}

static void	debug_dirs(t_dir *dirs)
{
	t_dir	*dir;
	t_entry	*entry;

	dir = dirs;
	while (dir)
	{
		if (dir->path)
			ft_printf("%s:\n", dir->path);
		entry = dir->entries;
		while (entry)
		{
			ft_printf("%s  ", entry->name);
			entry = entry->next;
		}
		ft_printf("\n\n");
		dir = dir->next;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	init_data(&data);
	if (parse_args(argv + 1, &data))
		return (1);
	debug_dirs(data.dirs);
	free_dirs(data.dirs);
	return (0);
}
