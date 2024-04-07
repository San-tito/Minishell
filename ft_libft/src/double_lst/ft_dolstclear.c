/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:21:15 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:21:22 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dolstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	tmp = *lst;
	while (tmp->next != NULL)
	{
		*lst = (*lst)->next;
		ft_dolstdelone(tmp, del);
		tmp = *lst;
	}
	ft_dolstdelone(tmp, del);
	*lst = NULL;
}
