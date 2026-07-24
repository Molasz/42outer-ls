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

static int	cmp_dir_time(t_dir *x, t_dir *y)
{
	if (x->stat.st_mtim.tv_sec != y->stat.st_mtim.tv_sec)
	{
		if (x->stat.st_mtim.tv_sec > y->stat.st_mtim.tv_sec)
			return (-1);
		return (1);
	}
	if (x->stat.st_mtim.tv_nsec != y->stat.st_mtim.tv_nsec)
	{
		if (x->stat.st_mtim.tv_nsec > y->stat.st_mtim.tv_nsec)
			return (-1);
		return (1);
	}
	return (ft_strcmp(x->path, y->path));
}

static void	dir_insert_time(t_dir **a, t_dir *b, int r_flag)
{
	t_dir	*tmp;
	int		cmp;

	if (!*a || (!r_flag && cmp_dir_time(*a, b) > 0)
		|| (r_flag && cmp_dir_time(*a, b) < 0))
	{
		b->next = (*a);
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next)
	{
		cmp = cmp_dir_time(tmp->next, b);
		if ((!r_flag && cmp > 0) || (r_flag && cmp < 0))
			break ;
		tmp = tmp->next;
	}
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
