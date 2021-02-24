/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:01:41 by adconsta          #+#    #+#             */
/*   Updated: 2021/01/28 19:10:51 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_gnlstrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_gnlstrncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;
	if (!src && !dest)
		return ;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
}

char	*ft_gnlstrjoin(char *storage, char *s2)
{
	char			*str;
	unsigned int	l1;
	unsigned int	l2;

	if (!storage && !s2)
		return (NULL);
	l1 = ft_gnlstrlen(storage);
	l2 = ft_gnlstrlen(s2);
	str = malloc(sizeof(char) * (l1 + l2 + 1));
	if (str == NULL)
	{
		free(storage);
		return (NULL);
	}
	ft_gnlstrncpy(str, storage, l1);
	ft_gnlstrncpy(str + l1, s2, l2);
	str[l1 + l2] = '\0';
	free(storage);
	return (str);
}

char	*ft_gnlstrdup(char *str)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_gnlstrlen(str);
	dest = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		look_for_newline(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
