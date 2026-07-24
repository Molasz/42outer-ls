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

static void	print_total(t_entry *entries)
{
	t_entry	*tmp;
	long	total;

	total = 0;
	tmp = entries;
	while (tmp)
	{
		total += tmp->stat.st_blocks;
		tmp = tmp->next;
	}
	ft_printf("total %ld\n", total / 2);
}

static void	print_normal(t_entry *entry)
{
	ft_printf("%s  ", entry->name);
}

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

static void	print_dirs(t_data *data)
{
	t_dir	*dir;

	dir = data->dirs;
	while (dir)
	{
		if (data->rec_flag || data->files || (data->dirs && data->dirs->next))
			ft_printf("%s:\n", dir->path);
		if (data->l_flag && dir->entries)
			print_total(dir->entries);
		print_entries(data, dir->entries);
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
