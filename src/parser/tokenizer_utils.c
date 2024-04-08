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

static void	clear_tokens()
{

}

static void	del_word(void *content)
{
	free(content);
}

static void	clear_words(t_list **words)
{
	ft_lstclear(words, del_word);
}

void	handle_error(t_list **words, t_list **tokens, char *error_msg)
{
	ft_printf(1, "%s", error_msg);
	clear_tokens(tokens)
	clear_words(words);
	exit(1);
}