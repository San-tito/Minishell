/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_utils.h"

char	handle_parentheses(t_token_range *token_range, t_list **tokens,
	char token_type)
{
	create_str_token(token_range, tokens);
	add_token(token_type, NULL, tokens);
	token_range->first++;
	return (1);
}

char	handle_and(t_token_range *token_range, t_list **tokens,
	t_list **words, char extended)
{
	if (!extended)
	{
		token_range->error = 1;
		handle_error(words, tokens, AND_ERROR);
		return (0);
	}
	create_str_token(token_range, tokens);
	add_token(AND_TOKEN, NULL, tokens);
	token_range->first += 2;
	return (2);
}

char	handle_or(t_token_range *token_range, t_list **tokens, char extended)
{
	char	token_type;

	create_str_token(token_range, tokens);
	if (extended)
		token_type = OR_TOKEN;
	else
		token_type = PIPE_TOKEN;
	add_token(token_type, NULL, tokens);
	if (token_type == OR_TOKEN)
	{
		token_range->first += 2;
		return (2);
	}
	token_range->first++;
	return (1);
}

char	handle_in(t_token_range *token_range, t_list **tokens, char extended)
{
	char	token_type;

	create_str_token(token_range, tokens);
	if (extended)
		token_type = HEREDOC_TOKEN;
	else
		token_type = INPUT_TOKEN;
	add_token(token_type, NULL, tokens);
	if (token_type == HEREDOC_TOKEN)
	{
		token_range->first += 2;
		return (2);
	}
	token_range->first++;
	return (1);
}

char	handle_out(t_token_range *token_range, t_list **tokens, char extended)
{
	char	token_type;

	create_str_token(token_range, tokens);
	if (extended)
		token_type = APPEND_TOKEN;
	else
		token_type = OUTPUT_TOKEN;
	add_token(token_type, NULL, tokens);
	if (token_type == APPEND_TOKEN)
	{
		token_range->first += 2;
		return (2);
	}
	token_range->first++;
	return (1);
}
