/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_error.h"
#include "error.h"

/*
 *	Called when there's an error separating words.
 */
char	handle_word_error(t_list **words, char *error_msg)
{
	internal_error(error_msg);
	clear_word_list(words);
	return (0);
}

/*
 *	Called when there's an error removing quotes.
 */
char	handle_token_error(t_list **tokens, char *error_msg)
{
	internal_error(error_msg);
	clear_tokens(tokens);
	return (0);
}

/*
 *	Called inside tokenizer when there's an error.
 */
char	handle_error(t_list **words, t_list **tokens, char *error_msg)
{
	internal_error(error_msg);
	clear_word_list(words);
	clear_tokens(tokens);
	return (0);
}

char	handle_checker_error(t_list **tokens, char *error_msg)
{
	internal_error("syntax error near unexpected token %s", error_msg);
	clear_tokens(tokens);
	return (0);
}
