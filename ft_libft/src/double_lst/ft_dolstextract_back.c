/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolstextract_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:21:15 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:21:22 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dolstextract_back(t_dlist **lst)
{
	t_dlist	*new_last;
	t_dlist	*lst_iter;

	if (*lst == NULL)
		return (NULL);
	lst_iter = *lst;
	new_last = NULL;
	while (lst_iter->next != NULL)
	{
		new_last = lst_iter;
		lst_iter = lst_iter->next;
	}
	if (new_last != NULL)
		new_last->next = NULL;
	else
		*lst = NULL;
	lst_iter->previous = NULL;
	return (lst_iter);
}
