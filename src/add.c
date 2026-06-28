/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:20:08 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/22 00:34:38 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_dir	*new_dir(char *path, struct stat *st)
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
	t_dir *tmp;

	if (!*a || (!r_flag && ft_strcmp((*a)->path, b->path) > 0) || (r_flag && ft_strcmp((*a)->path, b->path) < 0))
	{
		b->next = *a;
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ((!r_flag && ft_strcmp(tmp->next->path, b->path) < 0) || (r_flag && ft_strcmp(tmp->next->path, b->path) > 0)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

static void	dir_insert_time(t_dir **a, t_dir *b, int r_flag)
{
	t_dir *tmp;

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

static void dir_enqueue(t_data *data, t_dir *dir)
{
	if (data->t_flag)
		dir_insert_time(&data->dirs, dir, data->r_flag);
	else
		dir_insert_alpha(&data->dirs, dir, data->r_flag);
}

static int	read_dir_entry(t_data *data, t_dir *dir, DIR *dp)
{
	struct stat		st;
	struct dirent	*ent;
	char			*full_path;

	errno = 0;
	ent = readdir(dp);
	if (!ent)
	{
		if (errno)
			ft_printf("ft_ls: cannot read directory '%s': %s\n", dir->path, strerror(errno));
		return (-1);
	}
	if (!data->a_flag && ent->d_name[0] == '.')
		return (0);
	full_path = ft_concat_path(dir->path, ent->d_name);
	if (!full_path)
		return (1);
	if (lstat(full_path, &st) == -1)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", full_path, strerror(errno));
		free(full_path);
		return (0);
	}
	if (add_entry(data, &dir->entries, ent->d_name, &st))
		return (1);
	if (data->R_flag && S_ISDIR(st.st_mode) && ft_strcmp(ent->d_name, ".") != 0 && ft_strcmp(ent->d_name, "..") != 0)
		diradd(data, full_path);
	else
		free(full_path);
	return (0);
}

static int	ft_opendir(t_data *data, t_dir *dir)
{
	DIR	*dp;
	int	ret;

	dp = opendir(dir->path);
	if (!dp)
	{
		ft_printf("ft_ls: cannot open directory '%s': %s\n", dir->path, strerror(errno));
		return (0);
	}
	ret = 0;
	while (ret == 0)
	{
		ret = read_dir_entry(data, dir, dp);
		if (ret > 0)
			return (1);
	}
	if (closedir(dp))
	{
		ft_printf("ft_ls: cannot close directory '%s': %s\n", dir->path, strerror(errno));
		return (1);
	}
	return (0);
}

int	diradd(t_data *data, char *path)
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
		dir = new_dir(path, &st);
		if (!dir)
			return (1);
		dir_enqueue(data, dir);
		if (ft_opendir(data, dir))
			return (1);
	}
	else
	{
		add_entry(data, &data->files, path, &st);
		free(path);
	}
	return (0);
}
