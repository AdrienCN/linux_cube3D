/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:46:35 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/22 12:28:47 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			a;
	unsigned	int	nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb < 10)
	{
		a = nb + '0';
		write(fd, &a, 1);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		a = nb % 10 + '0';
		write(fd, &a, 1);
	}
}
