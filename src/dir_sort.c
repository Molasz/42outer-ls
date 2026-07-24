/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 01:36:48 by molasz-a          #+#    #+#             */
/*   Updated: 2026/07/24 01:36:49 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(char *path, struct stat *st)
{
	t_dir	*dir;

	dir = malloc(sizeof(t_dir));
	if (!dir)
		return (NULL);
	dir->path = path;
	dir->stat = *st;
	dir->entries = NULL;
	dir->next = NULL;
	return (dir);
}

static void	dir_insert_alpha(t_dir **a, t_dir *b, int r_flag)
{
	t_dir	*tmp;

	if (!*a || (!r_flag && ft_strcmp((*a)->path, b->path) > 0)
		|| (r_flag && ft_strcmp((*a)->path, b->path) < 0))
	{
		b->next = *a;
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ((!r_flag && ft_strcmp(tmp->next->path, b->path) < 0)
			|| (r_flag && ft_strcmp(tmp->next->path, b->path) > 0)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

static void	dir_insert_time(t_dir **a, t_dir *b, int r_flag)
{
	t_dir	*tmp;

	if (!*a || (!r_flag && (*a)->stat.st_mtime < b->stat.st_mtime)
		|| (r_flag && (*a)->stat.st_mtime >= b->stat.st_mtime))
	{
		b->next = (*a);
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next
		&& ((!r_flag && tmp->next->stat.st_mtime >= b->stat.st_mtime)
			|| (r_flag && tmp->next->stat.st_mtime < b->stat.st_mtime)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

void	dir_enqueue(t_data *data, t_dir *dir)
{
	if (data->t_flag)
		dir_insert_time(&data->dirs, dir, data->r_flag);
	else
		dir_insert_alpha(&data->dirs, dir, data->r_flag);
}
