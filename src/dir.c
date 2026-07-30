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

static void	read_path(t_data *d, t_dir *dir, struct dirent *en)
{
	char	*full_path;
	struct stat		st;


	full_path = ft_concat_path(dir->path, en->d_name);
	if (!full_path)
		free_exit(d, 1);
	if (lstat(full_path, &st) == -1)
		print_errno(d, "access", full_path);
	add_entry(d, &dir->entries, en->d_name, full_path);
	free(full_path);
}

static int	read_dir_entry(t_data *data, t_dir *dir, DIR *dp)
{
	struct dirent	*ent;

	errno = 0;
	ent = readdir(dp);
	if (!ent)
	{
		if (errno)
			print_errno(data, "read directory", dir->path);
		return (1);
	}
	if (ent->d_name[0] != '.' || data->a_flag)
		read_path(data, dir, ent);
	return (0);
}

static int	ft_opendir(t_data *data, t_dir *dir)
{
	DIR	*dp;
	int	ret;

	dp = opendir(dir->path);
	if (!dp)
	{
		print_errno(data, "open directory", dir->path);
		return (1);
	}
	ret = 0;
	while (ret == 0)
		ret = read_dir_entry(data, dir, dp);
	if (closedir(dp))
	{
		print_errno(data, "close directory", dir->path);
		free_exit(data, 1);
	}
	return (0);
}

t_dir	*read_subdir(t_data *data, char *path)
{
	t_dir		*dir;
	struct stat	st;

	if (lstat(path, &st) == -1)
	{
		print_errno(data, "access", path);
		free(path);
		return (NULL);
	}
	if (!S_ISDIR(st.st_mode))
		return (free(path), NULL);
	dir = new_dir(path, &st);
	if (!dir)
	{
		free(path);
		free_exit(data, 1);
	}
	if (ft_opendir(data, dir))
	{
		free(path);
		free(dir);
		return (NULL);
	}
	return (dir);
}

void	add_dir(t_data *data, char *path)
{
	t_dir		*dir;
	struct stat	st;

	if (lstat(path, &st) == -1)
	{
		print_errno(data, "access", path);
		free(path);
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
