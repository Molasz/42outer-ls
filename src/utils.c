/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 00:39:44 by molasz-a          #+#    #+#             */
/*   Updated: 2026/06/29 00:39:46 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	i = ft_strlcpy(str, s1, len1 + 1);
	if (slash)
		str[i++] = '/';
	ft_strlcpy(str + i, s2, len2 + 1);
	return (str);
}

char	*ft_ternary(int con, char *a, char *b)
{
	if (con)
		return (a);
	else
		return (b);
}
