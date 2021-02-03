/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:23:30 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/19 15:46:31 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert_str(char *str, unsigned int nb, unsigned int size)
{
	while (nb >= 10)
	{
		str[size] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	str[size] = nb % 10 + '0';
	if (size > 0)
	{
		size--;
		str[size] = '-';
	}
}

char		*ft_itoa(int n)
{
	char			*str;
	unsigned	int	size;
	unsigned	int	tmp;
	unsigned	int	nbr;

	size = (n >= 0 ? 1 : 2);
	nbr = (n >= 0 ? n : -n);
	tmp = nbr;
	while (tmp >= 10)
	{
		size++;
		tmp = tmp / 10;
	}
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_convert_str(str, nbr, (size - 1));
	str[size] = '\0';
	return (str);
}
