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

char *symlink_target(char *path, struct stat *st)
{
    char    *target;
    ssize_t len;

    if (!S_ISLNK(st->st_mode))
        return (NULL);
    target = malloc(st->st_size + 1);
    if (!target)
        return (NULL);
    len = readlink(path, target, st->st_size + 1);
    if (len == -1)
    {
        free(target);
        return (NULL);
    }
    target[len] = '\0';
    return (target);
}

static t_entry	*new_entry(char *name, char *full_path, struct stat *st)
{
	t_entry	*entry;

	entry = malloc(sizeof (t_entry));
	if (!entry)
		return (NULL);
	entry->name = ft_strdup(name);
	if (!entry->name)
	{
		free(entry);
		return (NULL);
	}
	entry->symlink = symlink_target(full_path, st);
	entry->stat = *st;
	entry->next = NULL;
	return (entry);
}

static void	entry_insert_alpha(t_entry **a, t_entry *b, int r_flag)
{
	t_entry *tmp;

	if (!*a || (!r_flag && ft_strcmp((*a)->name, b->name) > 0) || (r_flag && ft_strcmp((*a)->name, b->name) < 0))
	{
		b->next = *a;
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ( (!r_flag && ft_strcmp(tmp->next->name, b->name) < 0) || (r_flag && ft_strcmp(tmp->next->name, b->name) > 0)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

static void	entry_insert_time(t_entry **a, t_entry *b, int r_flag)
{
	t_entry *tmp;

	if (!*a || (!r_flag && (*a)->stat.st_mtime < b->stat.st_mtime) || (r_flag && (*a)->stat.st_mtime >= b->stat.st_mtime))
	{
		b->next = (*a);
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ((!r_flag && tmp->next->stat.st_mtime >= b->stat.st_mtime) || (r_flag && tmp->next->stat.st_mtime < b->stat.st_mtime)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

void	add_entry(t_data *data, t_entry **entries, char *name, char *full_path, struct stat *st)
{
	t_entry			*entry;

	entry = new_entry(name, full_path, st);
	if (!entry)
		free_exit(data, 1);
	if (data->t_flag)
		entry_insert_time(entries, entry, data->r_flag);
	else
		entry_insert_alpha(entries, entry, data->r_flag);
}
