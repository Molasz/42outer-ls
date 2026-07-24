/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:39:08 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/29 00:39:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_entry	*new_entry(char *name, char *full_path)
{
	t_entry		*entry;
	struct stat	st;

	entry = malloc(sizeof (t_entry));
	if (!entry)
		return (NULL);
	entry->name = ft_strdup(name);
	if (!entry->name)
	{
		free(entry);
		return (NULL);
	}
	lstat(full_path, &st);
	entry->symlink = symlink_target(full_path, &st);
	entry->stat = st;
	entry->next = NULL;
	return (entry);
}

static void	entry_insert_alpha(t_entry **a, t_entry *b, int r_flag)
{
	t_entry	*tmp;

	if (!*a || (!r_flag && ft_strcmp((*a)->name, b->name) > 0)
		|| (r_flag && ft_strcmp((*a)->name, b->name) < 0))
	{
		b->next = *a;
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ((!r_flag && ft_strcmp(tmp->next->name, b->name) < 0)
			|| (r_flag && ft_strcmp(tmp->next->name, b->name) > 0)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

static int	cmp_entry_time(t_entry *x, t_entry *y)
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
	return (ft_strcmp(x->name, y->name));
}

static void	entry_insert_time(t_entry **a, t_entry *b, int r_flag)
{
	t_entry	*tmp;
	int		cmp;

	if (!*a || (!r_flag && cmp_entry_time(*a, b) > 0)
		|| (r_flag && cmp_entry_time(*a, b) < 0))
	{
		b->next = (*a);
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next)
	{
		cmp = cmp_entry_time(tmp->next, b);
		if ((!r_flag && cmp > 0) || (r_flag && cmp < 0))
			break ;
		tmp = tmp->next;
	}
	b->next = tmp->next;
	tmp->next = b;
}

void	add_entry(t_data *data, t_entry **entries, char *name, char *full_path)
{
	t_entry			*entry;

	entry = new_entry(name, full_path);
	if (!entry)
		free_exit(data, 1);
	if (data->t_flag)
		entry_insert_time(entries, entry, data->r_flag);
	else
		entry_insert_alpha(entries, entry, data->r_flag);
}
