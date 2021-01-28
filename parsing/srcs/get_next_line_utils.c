/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:01:41 by adconsta          #+#    #+#             */
/*   Updated: 2021/01/28 15:50:36 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strncpy(char *dest, char *src, int n)
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

char	*ft_gnljoin(char *storage, char *s2)
{
	char			*str;
	unsigned int	l1;
	unsigned int	l2;

	if (!storage && !s2)
		return (NULL);
	l1 = ft_strlen(storage);
	l2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (l1 + l2 + 1));
	if (str == NULL)
	{
		free(storage);
		return (NULL);
	}
	ft_strncpy(str, storage, l1);
	ft_strncpy(str + l1, s2, l2);
	str[l1 + l2] = '\0';
	free(storage);
	return (str);
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
