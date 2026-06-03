/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:05:00 by molasz            #+#    #+#             */
/*   Updated: 2026/06/03 15:20:44 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0' ))
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_concat_path(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (i < len1 + len2 + 1)
	{
		str[i] = s2[i - (len1 + 1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}

