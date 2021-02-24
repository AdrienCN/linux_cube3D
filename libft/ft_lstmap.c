/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:33:13 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/22 15:06:13 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *b_list;
	t_list *n_node;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	if (!(n_node = ft_lstnew(f(tmp->content))))
		return (NULL);
	b_list = n_node;
	tmp = tmp->next;
	while (tmp)
	{
		n_node = ft_lstnew(f(tmp->content));
		if (n_node == NULL)
		{
			ft_lstclear(&b_list, del);
			return (NULL);
		}
		ft_lstadd_back(&b_list, n_node);
		tmp = tmp->next;
	}
	return (b_list);
}
