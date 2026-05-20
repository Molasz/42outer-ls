/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:05:00 by molasz            #+#    #+#             */
/*   Updated: 2026/05/20 13:29:44 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0' ))
		i++;
	return (s1[i] - s2[i]);
}

t_path	*ft_pathnew(char *str)
{
	t_path	*path;

	path = malloc(sizeof (t_path));
	if (!path)
		return (NULL);
	path->path = str;
	path->next = NULL;
	return (path);
}

int	ft_lstadd_alpha(t_path **lst, char *str)
{
	t_path	*path;
	t_path	*tmp;

    path = ft_pathnew(str);
    if (!path)
		return (1);
    if (lstat(str, &path->stat) == -1)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", str, strerror(errno));
		return (0);
	}
	if (!*lst || ft_strcmp((*lst)->path, str) > 0)
	{
		path->next = *lst;
		*lst = path;
    }
    else
    {
        tmp = *lst;
        while (tmp->next && ft_strcmp(tmp->next->path, str) < 0)
            tmp = tmp->next;
        path->next = tmp->next;
        tmp->next = path;
    }
    return (0);
}
