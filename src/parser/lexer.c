/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 12:31:16 by sguzman          ###   ########.fr       */
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

static t_list	*create_tokens(char *job, char *err)
{
	t_list	*words;
	t_list	*tokens;

	words = separate_words(job);
	if (words == NULL)
	{
		*err = 1;
		return (NULL);
	}
	remove_empty_words(&words);
	if (words == NULL)
	{
		*err = -1;
		return (NULL);
	}
	tokens = tokenizer(&words);
	if (tokens == NULL)
	{
		*err = 1;
		return (NULL);
	}
	clear_word_list(&words);
	return (tokens);
}

t_list	*lexer(char *job, char *err)
{
	t_list	*tokens;

	tokens = create_tokens(job, err);
	if (tokens == NULL)
		return (NULL);
	expansor(&tokens);
	remove_quotes(&tokens);
	if (!check_tokens(&tokens))
	{
		*err = 1;
		return (NULL);
	}
	return (tokens);
}
