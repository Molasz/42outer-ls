/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:05:00 by molasz            #+#    #+#             */
/*   Updated: 2026/06/16 16:46:30 by molasz-a         ###   ########.fr       */
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
	int		slash;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	slash = !len1 || s1[len1 - 1] != '/';
	str = malloc(len1 + len2 + slash + 1);
	printf("MALLOC %d\n", len1 + len2 + slash + 1);
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
		printf("%c ", s2[i]);
		str[len1 + slash + 1] = s2[i];
		i++;
	}
	str[len1 + len2 + slash] = '\0';
	printf("\nEND %s\n", str);
	return (str);
}

