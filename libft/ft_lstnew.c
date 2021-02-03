/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 10:11:20 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/21 18:11:03 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list *new_n;

	if (!(new_n = malloc(sizeof(*new_n))))
		return (NULL);
	new_n->content = data;
	new_n->next = NULL;
	return (new_n);
}
