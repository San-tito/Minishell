/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear_structs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"


void	del_word(void *content)
{
	free(content);
}

void	clear_words(t_list **words)
{
	ft_lstclear(words, del_word);
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->content != NULL)
		free(token->content);
	free(token);
}

void	clear_tokens(t_list **tokens)
{
	ft_lstclear(tokens, del_token);
}
