/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:51:46 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/22 12:21:54 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned	char	*d;
	unsigned	char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		d = ft_memcpy(dest, src, n);
	return (dest);
}
