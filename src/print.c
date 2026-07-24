/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:40:24 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/29 00:40:25 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_entries(t_data *data, t_entry *entries)
{
	t_entry	*entry;
	void	(*fn)(t_entry *);

	if (data->l_flag)
		fn = print_list;
	else
		fn = print_normal;
	entry = entries;
	while (entry)
	{
		fn(entry);
		entry = entry->next;
	}
	if (!data->l_flag && entries)
		ft_printf("\n");
}

static void	print_dir_content(t_data *data, t_dir *dir, int print_header);

static void	explore_subdirs(t_data *data, t_dir *dir)
{
	t_entry	*entry;
	char	*subpath;
	t_dir	*subdir;

	entry = dir->entries;
	while (entry)
	{
		if (S_ISDIR(entry->stat.st_mode) && ft_strcmp(entry->name, ".") != 0
			&& ft_strcmp(entry->name, "..") != 0)
		{
			subpath = ft_concat_path(dir->path, entry->name);
			if (!subpath)
				free_exit(data, 1);
			subdir = read_subdir(data, subpath);
			if (subdir)
			{
				ft_printf("\n");
				print_dir_content(data, subdir, 1);
				free_dirs(subdir);
			}
		}
		entry = entry->next;
	}
}

static void	print_dir_content(t_data *data, t_dir *dir, int print_header)
{
	if (print_header)
		ft_printf("%s:\n", dir->path);
	if (data->l_flag && dir->entries)
		print_total(dir->entries);
	print_entries(data, dir->entries);
	if (data->rec_flag)
		explore_subdirs(data, dir);
}

static void	print_dirs(t_data *data)
{
	t_dir	*dir;

	dir = data->dirs;
	while (dir)
	{
		print_dir_content(data, dir,
			(data->rec_flag || data->files || (data->dirs && data->dirs->next))
			);
		dir = dir->next;
		if (dir)
			ft_printf("\n");
	}
}

void	print_data(t_data *data)
{
	if (data->files)
		print_entries(data, data->files);
	if (data->files && data->dirs)
		ft_printf("\n");
	if (data->dirs)
		print_dirs(data);
}
