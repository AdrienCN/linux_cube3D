/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:58:36 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/18 11:09:13 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned	char	*tmp;
	unsigned	char	a;
	size_t				i;

	a = (unsigned char)c;
	i = 0;
	tmp = (unsigned char*)s;
	while (i < n)
	{
		if (*tmp == a)
			return ((void*)(tmp));
		tmp++;
		i++;
	}
	return (NULL);
}
