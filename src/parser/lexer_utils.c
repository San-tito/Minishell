/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	del_word(void *content)
{
	free(content);
}

void	clear_words(t_list **words)
{
	ft_lstclear(words, del_word);
}

void	remove_empty_words(t_list **words)
{
	t_list	*current;

	current = *words;
	if (current == NULL)
		return ;
	if (*(char *)(current->content) == '\0')
	{
		*words = current->next;
		ft_lstdelone(current, del_word);
		remove_empty_words(words);
	}
	else
		remove_empty_words(&(current->next));
}
