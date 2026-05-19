/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 11:58:35 by molasz-a          #+#    #+#             */
/*   Updated: 2026/05/19 21:20:48 by molasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_data(t_ls *data)
{
	data->paths = NULL;
	data->l_flag = 0;
	data->R_flag = 0;
	data->a_flag = 0;
	data->r_flag = 0;
	data->t_flag = 0;
}

static void	free_data(t_ls *data)
{
	t_path	*path;
	t_path	*tmp;

	if (data->paths)
	{
		path = data->paths;
		while (path)
		{
			tmp = path->next;
			free(path);
			path = tmp;
		}
	}
}

static void    debug_paths(t_path *path)
{
    struct stat *s;

    while (path)
    {
		s = &path->stat;
		ft_printf("=== %s ===\n", path->path);
		ft_printf("st_mode:   %u\n", s->st_mode);
		ft_printf("st_ino:    %lu\n", s->st_ino);
		ft_printf("st_nlink:  %lu\n", s->st_nlink);
		ft_printf("st_uid:    %u\n", s->st_uid);
		ft_printf("st_gid:    %u\n", s->st_gid);
		ft_printf("st_size:   %ld\n", s->st_size);
		ft_printf("st_blocks: %ld\n", s->st_blocks);
		ft_printf("st_mtime:  %ld\n", s->st_mtim.tv_sec);
		ft_printf("is_dir:    %d\n", S_ISDIR(s->st_mode));
		ft_printf("is_lnk:    %d\n", S_ISLNK(s->st_mode));
		ft_printf("is_reg:    %d\n\n", S_ISREG(s->st_mode));
        path = path->next;
    }
}

int	main(int argc, char **argv)
{
	t_ls	data;

	init_data(&data);
	if (argc > 1)
		parse_args(argv + 1, &data);
	debug_paths(data.paths);
	free_data(&data);
	return (0);
}
