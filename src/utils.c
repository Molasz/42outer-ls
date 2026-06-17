/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:05:00 by molasz            #+#    #+#             */
/*   Updated: 2026/06/17 15:39:47 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	char	c1;
	char	c2;

	i = 0;
	c1 = ft_tolower(s1[i]);
	c2 = ft_tolower(s2[i]);
	while (c1 == c2 && (c1 != '\0' && c2 != '\0' ))
	{
		i++;
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[i]);
	}
	return (c1 - c2);
}

char	*ft_concat_path(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		slash;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	slash = !len1 || s1[len1 - 1] != '/';
	str = malloc(len1 + len2 + slash + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	if (slash)
		str[i] = '/';
	i = 0;
	while (i < len2)
	{
		str[len1 + slash + i] = s2[i];
		i++;
	}
	str[len1 + len2 + slash] = '\0';
	return (str);
}

