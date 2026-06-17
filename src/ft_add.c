/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:20:08 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/17 16:06:54 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_entry	*ft_entrynew(char *name, struct stat *st)
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
	entry->stat = *st;
	entry->next = NULL;
	return (entry);
}

static void	entry_insert_alpha(t_dir *dir, t_entry*entry)
{
	t_entry *tmp;

	if (!dir->entries || ft_strcmp(dir->entries->name, entry->name) > 0)
	{
		entry->next = dir->entries;
		dir->entries = entry;
		return ;
	}
	tmp = dir->entries;
	while (tmp->next && ft_strcmp(tmp->next->name, entry->name) < 0)
		tmp = tmp->next;
	entry->next = tmp->next;
	tmp->next = entry;
}

static void	entry_insert_time(t_dir *dir, t_entry *entry)
{
	t_entry *tmp;

	if (!dir->entries || dir->entries->stat.st_mtime < entry->stat.st_mtime)
	{
		entry->next = dir->entries;
		dir->entries = entry;
		return ;
	}
	tmp = dir->entries;
	while (tmp->next && tmp->next->stat.st_mtime >= entry->stat.st_mtime)
		tmp = tmp->next;
	entry->next = tmp->next;
	tmp->next = entry;
}

static t_dir	*ft_dirnew(char *path)
{
	t_dir	*dir;

	dir = malloc(sizeof(t_dir));
	if (!dir)
		return (NULL);
	dir->path = path;
	dir->entries = NULL;
	dir->next = NULL;
	return (dir);
}

static void dir_enqueue(t_data *data, t_dir *dir)
{
	t_dir *tmp;
	
	if (!data->dirs || !data->dirs->path || ft_strcmp(data->dirs->path, dir->path) > 0)
	{
		dir->next = data->dirs;
		data->dirs = dir;
		return ;
	}
	tmp = data->dirs;
	while (tmp->next && tmp->next->path && ft_strcmp(tmp->next->path, dir->path) < 0)
		tmp = tmp->next;
	dir->next = tmp->next;
	tmp->next = dir;
}

static int	ft_opendir(t_data *data, t_dir *dir)
{
	struct dirent	*ent;
	struct stat		st;
	DIR				*dp;
	char			*full_path;
	t_entry			*entry;

	dp = opendir(dir->path);
	if (!dp)
	{
		ft_printf("ft_ls: cannot open directory '%s': %s\n", dir->path, strerror(errno));
		return (0);
	}
	while (1)
	{
		errno = 0;
		ent = readdir(dp);
		if (!ent)
		{
			if (errno)
				ft_printf("ft_ls: cannot read directory '%s': %s\n", dir->path, strerror(errno));
			break ;
		}
		if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name,"..") || (!data->a_flag && ent->d_name[0] == '.'))
			continue ;
		full_path = ft_concat_path(dir->path, ent->d_name);
		if (!full_path)
		{
			closedir(dp);
			return (1);
		}
		if (lstat(full_path, &st) == -1)
		{
			ft_printf("ft_ls: cannot access '%s': %s\n", full_path, strerror(errno));
			free(full_path);
			continue ;
		}
		entry = ft_entrynew(ent->d_name, &st);
		if (!entry)
		{
			closedir(dp);
			return (1);
		}
		if (data->t_flag)
			entry_insert_time(dir, entry);
		else
			entry_insert_alpha(dir, entry);
		if (data->R_flag && S_ISDIR(st.st_mode))
			ft_diradd(data, full_path);
		else
			free(full_path);
	}
	if (closedir(dp))
	{
		ft_printf("ft_ls: cannot close directory '%s': %s\n", dir->path, strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_diradd(t_data *data, char *path)
{
	t_dir		*dir;
	struct stat	st;

	if (lstat(path, &st) == -1)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return (0);
	}
	if (S_ISDIR(st.st_mode))
	{
		dir = ft_dirnew(path);
		if (!dir)
			return (1);
		dir_enqueue(data, dir);
		if (ft_opendir(data, dir))
			return (1);
	}
	else
	{
		if (!data->dirs || data->dirs->path != NULL)
		{
			dir = ft_dirnew(NULL);
			if (!dir)
				return (1);
			dir->next = data->dirs;
			data->dirs = dir;
		}
		t_entry *entry = ft_entrynew(path, &st);
		if (!entry)
			return (1);
		if (data->t_flag)
			entry_insert_time(data->dirs, entry);
		else
			entry_insert_alpha(data->dirs, entry);
	}
	return (0);
}
