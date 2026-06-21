/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 16:27:10 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/22 01:39:22 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void print_total(t_entry *entries)
{
    t_entry *tmp;
    long    total;

    total = 0;
    tmp = entries;
    while (tmp)
    {
        total += tmp->stat.st_blocks;
        tmp = tmp->next;
    }
    ft_printf("total %ld\n", total / 2);
}

static void print_permissions(mode_t mode)
{
	char type;
		
	if (S_ISDIR(mode))	   type = 'd';
	else if (S_ISLNK(mode))  type = 'l';
	else if (S_ISCHR(mode))  type = 'c';
	else if (S_ISBLK(mode))  type = 'b';
	else if (S_ISFIFO(mode)) type = 'p';
	else if (S_ISSOCK(mode)) type = 's';
	else					 type = '-';
	ft_printf("%c", type);
	ft_printf("%c", (mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXUSR) ? 'x' : '-');
	ft_printf("%c", (mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXGRP) ? 'x' : '-');
	ft_printf("%c", (mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

static void print_list(t_entry *entry)
{
	struct passwd   *pw;
	struct group	*gr;
	char			*time;

	pw = getpwuid(entry->stat.st_uid);
	gr = getgrgid(entry->stat.st_gid);
	time = ctime(&entry->stat.st_mtime);

	print_permissions(entry->stat.st_mode);
	ft_printf(" %d", entry->stat.st_nlink);
	ft_printf(" %s", pw ? pw->pw_name : "?");
	ft_printf(" %s", gr ? gr->gr_name : "?");
	ft_printf(" %d", entry->stat.st_size);
	ft_printf(" %.12s", time + 4);
	ft_printf(" %s\n", entry->name);
}

static void print_normal(t_entry *entry)
{
	ft_printf("%s  ", entry->name);
}
static void	print_dir(t_dir *dir, void (*fn)(t_entry *))
{
	t_entry	*entry;

	entry = dir->entries;
	while (entry)
	{
		fn(entry);
		entry = entry->next;
	}
}

void	print_dirs(t_data *data)
{
	t_dir	*dir;
	void	(*fn)(t_entry *);
	
	if (data->l_flag)
		fn = print_list;
	else
		fn = print_normal;
	dir = data->dirs;
	while (dir)
	{
		if (data->R_flag || (data->dirs && data->dirs->next))
			ft_printf("%s:\n", dir->path);
		if (data->l_flag)
			print_total(dir->entries);
		print_dir(dir, fn);
		dir = dir->next;
		if (dir)
			ft_printf("\n");
		ft_printf("\n");
	}
}
