/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:23:35 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 17:48:34 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_node(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*tmp;
	t_list	*node;

	tmp = (f)(lst->content);
	node = ft_lstnew(tmp);
	if (node == NULL)
		del(tmp);
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_to_return;
	t_list	*node;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	lst_to_return = NULL;
	node = get_node(lst, f, del);
	while (lst->next != NULL && node != NULL)
	{
		ft_lstadd_back(&lst_to_return, node);
		lst = lst->next;
		node = get_node(lst, f, del);
	}
	if (node == NULL)
	{
		ft_lstclear(&lst_to_return, del);
		return (NULL);
	}
	ft_lstadd_back(&lst_to_return, node);
	return (lst_to_return);
}
