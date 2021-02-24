/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:04:22 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/22 12:31:34 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *ptr, const void *ptr2, size_t num)
{
	unsigned	char	*s1;
	unsigned	char	*s2;

	s1 = (unsigned char*)ptr;
	s2 = (unsigned char*)ptr2;
	while (num && *s1 == *s2)
	{
		s1++;
		s2++;
		num--;
	}
	if (num == 0)
		return (0);
	return (*s1 - *s2);
}
