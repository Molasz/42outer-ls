/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 02:06:39 by molasz-a          #+#    #+#             */
/*   Updated: 2026/07/24 02:06:44 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_normal(t_entry *entry)
{
	ft_printf("%s  ", entry->name);
}

static char	get_permission_type(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

static void	print_permissions(mode_t mode)
{
	ft_printf("%c", get_permission_type(mode));
	ft_printf("%s", ft_ternary(mode & S_IRUSR, "r", "-"));
	ft_printf("%s", ft_ternary(mode & S_IWUSR, "w", "-"));
	if (mode & S_ISUID)
		ft_printf("%s", ft_ternary(mode & S_IXUSR, "s", "S"));
	else
		ft_printf("%s", ft_ternary(mode & S_IXUSR, "x", "-"));
	ft_printf("%s", ft_ternary(mode & S_IRGRP, "r", "-"));
	ft_printf("%s", ft_ternary(mode & S_IWGRP, "w", "-"));
	if (mode & S_ISGID)
		ft_printf("%s", ft_ternary(mode & S_IXGRP, "s", "S"));
	else
		ft_printf("%s", ft_ternary(mode & S_IXGRP, "x", "-"));
	ft_printf("%s", ft_ternary(mode & S_IROTH, "r", "-"));
	ft_printf("%s", ft_ternary(mode & S_IWOTH, "w", "-"));
	if (mode & S_ISVTX)
		ft_printf("%s", ft_ternary(mode & S_IXOTH, "t", "T"));
	else
		ft_printf("%s", ft_ternary(mode & S_IXOTH, "x", "-"));
}

void	print_list(t_entry *entry)
{
	struct passwd	*pw;
	struct group	*gr;
	char			*time;

	pw = getpwuid(entry->stat.st_uid);
	gr = getgrgid(entry->stat.st_gid);
	time = ctime(&entry->stat.st_mtime);
	print_permissions(entry->stat.st_mode);
	ft_printf(" %d", entry->stat.st_nlink);
	ft_printf(" %s", ft_ternary(pw != 0, (char *)pw->pw_name, "?"));
	ft_printf(" %s", ft_ternary(gr != 0, (char *)gr->gr_name, "?"));
	ft_printf(" %4d", entry->stat.st_size);
	ft_printf(" %.12s", time + 4);
	if (entry->symlink)
		ft_printf(" %s -> %s\n", entry->name, entry->symlink);
	else
		ft_printf(" %s\n", entry->name);
}

void	print_total(t_entry *entries)
{
	t_entry	*tmp;
	long	total;

	total = 0;
	tmp = entries;
	while (tmp)
	{
		total += tmp->stat.st_blocks;
		tmp = tmp->next;
	}
	ft_printf("total %ld\n", total / 2);
}
