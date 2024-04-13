/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create_simple_command.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 13:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static char	is_token_boundary(t_token *token)
{
	char	type;

	type = token->type;
	if (type == AND_TOKEN || type == PIPE_TOKEN || type == OR_TOKEN)
		return (1);
	return (0);
}

static t_instruction	select_instruction(char redirect)
{
	if (redirect == OUTPUT_TOKEN)
		return (r_output_direction);
	if (redirect == INPUT_TOKEN)
		return (r_input_direction);
	if (redirect == APPEND_TOKEN)
		return (r_appending_to);
	return (r_reading_until);
}

static t_command	*create_simple_command(t_list **tokens)
{
	t_word_list	*words;
	t_redirect	*redirect;
	t_token		*token;
	char		redir;

	while (*tokens && !is_token_boundary((t_token *)((*tokens)->data)))
	{
		token = (t_token *)((*tokens)->data);
		if (token->type == STR_TOKEN)
			words = make_word_list(token->data, words);
		else
		{
			(*tokens)++;
			redir = token->type;
			token = (t_token *)((*tokens)->data);
			redirect = make_redirection(token->data, select_instruction(redir), redirect);
		}
		(*tokens)++;
	}
	return (make_simple_command(words, redirect));
}
