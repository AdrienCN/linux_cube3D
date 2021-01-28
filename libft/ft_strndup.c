/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 10:45:03 by adconsta          #+#    #+#             */
/*   Updated: 2021/01/28 14:24:26 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*new_s;

	i = 0;
	new_s = NULL;
	new_s = malloc(sizeof(char) * (n + 1));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
