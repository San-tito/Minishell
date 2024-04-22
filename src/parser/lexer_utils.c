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

void	handle_word_error(t_list **words, char *error_msg)
{
	ft_printf("%s", error_msg);
	clear_word_list(words);
	exit(1);
}

void	handle_token_error(t_list **tokens, char *error_msg)
{
	ft_printf("%s", error_msg);
	clear_tokens(tokens);
	exit(1);
}

void	handle_error(t_list **words, t_list **tokens, char *error_msg)
{
	ft_printf("%s", error_msg);
	clear_tokens(tokens);
	clear_word_list(words);
	exit(1);
}
