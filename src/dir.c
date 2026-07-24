/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:39:57 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/29 00:39:58 by molasz-a         ###   ########.fr       */
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

static void	read_path(t_data *d, t_dir *dir, struct stat st, struct dirent *en)
{
	char			*full_path;

	full_path = ft_concat_path(dir->path, en->d_name);
	if (!full_path)
		free_exit(d, 1);
	if (lstat(full_path, &st) == -1)
	{
		print_errno("access", full_path);
		free(full_path);
	}
	add_entry(d, &dir->entries, en->d_name, full_path);
	if (d->rec_flag && S_ISDIR(st.st_mode)
		&& ft_strcmp(en->d_name, ".") != 0
		&& ft_strcmp(en->d_name, "..") != 0)
		add_dir(d, full_path);
	else
		free(full_path);
}

static int	read_dir_entry(t_data *data, t_dir *dir, DIR *dp)
{
	struct stat		st;
	struct dirent	*ent;

	errno = 0;
	ent = readdir(dp);
	if (!ent)
	{
		if (errno)
			print_errno("read directory", dir->path);
		return (1);
	}
	if (ent->d_name[0] != '.' || data->a_flag)
		read_path(data, dir, st, ent);
	return (0);
}

static void	ft_opendir(t_data *data, t_dir *dir)
{
	DIR	*dp;
	int	ret;

	dp = opendir(dir->path);
	if (!dp)
	{
		print_errno("open directory", dir->path);
		return ;
	}
	ret = 0;
	while (ret == 0)
		ret = read_dir_entry(data, dir, dp);
	if (closedir(dp))
	{
		print_errno("close directory", dir->path);
		free_exit(data, 1);
	}
}

void	add_dir(t_data *data, char *path)
{
	t_dir		*dir;
	struct stat	st;

	if (lstat(path, &st) == -1)
	{
		print_errno("access", path);
		return ;
	}
	if (S_ISDIR(st.st_mode))
	{
		dir = new_dir(path, &st);
		if (!dir)
		{
			free(path);
			free_exit(data, 1);
		}
		dir_enqueue(data, dir);
		ft_opendir(data, dir);
	}
	else
	{
		add_entry(data, &data->files, path, path);
		free(path);
	}
}
