/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 01:20:21 by molasz-a          #+#    #+#             */
/*   Updated: 2026/07/24 01:20:22 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_entries(t_entry *entry)
{
	t_entry	*tmp;

	while (entry)
	{
		tmp = entry->next;
		free(entry->name);
		if (entry->symlink)
			free(entry->symlink);
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

void	free_exit(t_data *data, int exitCode)
{
	free_dirs(data->dirs);
	free_entries(data->files);
	exit(exitCode);
}
