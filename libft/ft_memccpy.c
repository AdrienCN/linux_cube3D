/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:49:01 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/22 12:20:47 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *m_dst;
	unsigned char *m_src;

	m_dst = (unsigned char*)dest;
	m_src = (unsigned char *)src;
	while (n--)
	{
		*m_dst = *m_src;
		if (*m_src == (unsigned char)c)
			return ((void*)m_dst + 1);
		m_src++;
		m_dst++;
	}
	return (NULL);
}
