/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:42:45 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/16 17:07:54 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_length(t_generic_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_generic_list	*list_append(t_generic_list *head, t_generic_list *tail)
{
	t_generic_list	*t_head;

	if (head == 0 || tail == 0)
		return (tail);
	t_head = head;
	while (t_head->next)
		t_head = t_head->next;
	t_head->next = tail;
	return (head);
}

void	list_remove(t_generic_list **list)
{
	t_generic_list	*temp;

	temp = *list;
	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

char	**wlist_to_carray(t_word_list *list)
{
	int		count;
	char	**array;

	count = list_length((t_generic_list *)list);
	array = sh_malloc((1 + count) * sizeof(char *));
	count = 0;
	while (list)
	{
		array[count] = list->word;
		list = list->next;
		count++;
	}
	array[count] = NULL;
	return (array);
}
