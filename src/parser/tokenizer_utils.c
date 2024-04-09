/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"

static void	del_token(void *content)
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

void	handle_error(t_list **words, t_list **tokens, char *error_msg)
{
	ft_printf(1, "%s", error_msg);
	clear_tokens(tokens);
	clear_words(words);
	exit(1);
}
