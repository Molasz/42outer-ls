/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:20:08 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/03 15:40:52 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_path	*ft_pathnew(char *str)
{
	t_path	*path;

	path = malloc(sizeof (t_path));
	if (!path)
		return (NULL);
	path->path = str;
	path->next = NULL;
	return (path);
}

static int	ft_opendir(t_data *data, t_path *path)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*new_path;

	dir = opendir(path->path);
	if (!dir)
		return (1);
	while (1)
	{
		ent = readdir(dir);
		if (ent)
		{
			if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name,"..") || (!data->a_flag && ent->d_name[0] == '.'))
				continue ;
			new_path = ft_concat_path(path->path, ent->d_name);
			ft_lstadd_alpha(data, new_path, 0);
		}
		else
			break ;
	}
	if (closedir(dir))
		return (1);
	return (0);
}

void	update_lst(t_data *data, t_path *path)
{
	t_path	*tmp;

	if (!data->paths || ft_strcmp(data->paths->path, path->path) > 0)
	{
		path->next = data->paths;
		data->paths = path;
	}
	else
	{
		tmp = data->paths;
		while (tmp->next && ft_strcmp(tmp->next->path, path->path) < 0)
			tmp = tmp->next;
		path->next = tmp->next;
		tmp->next = path;
	}
}

int	ft_lstadd_alpha(t_data *data, char *str, int isParam)
{
	t_path	*path;

	path = ft_pathnew(str);
	if (!path)
		return (1);
	if (lstat(str, &path->stat) == -1)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", str, strerror(errno));
		return (0);
	}
	if ((data->R_flag || isParam) && S_ISDIR(path->stat.st_mode))
	{
		ft_opendir(data, path);
		free(path);
	}
	else
		update_lst(data, path);
	return (0);
}
