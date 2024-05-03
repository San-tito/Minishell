/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

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

t_list	*lexer(char *job)
{
	t_list	*words;
	t_list	*tokens;

	words = separate_words(job);
	if (words == NULL)
		return (NULL);
	remove_empty_words(&words);
	tokens = tokenizer(&words);
	if (tokens == NULL)
		return (NULL);
	clear_word_list(&words);
	if (!remove_quotes(&tokens))
		return (NULL);
	if (!check_tokens(&tokens))
		return (NULL);
	return (tokens);
}
