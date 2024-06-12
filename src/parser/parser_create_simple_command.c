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

#include "parser_utils.h"

static char	is_token_boundary(t_token *token)
{
	char	type;

	type = token->type;
	if (type == AND_TOKEN || type == PIPE_TOKEN || type == OR_TOKEN
		|| type == OPEN_PAR_TOKEN || type == CLOSE_PAR_TOKEN)
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

t_command	*create_simple_command(t_list **tokens)
{
	t_word_list	*words;
	t_redirect	*redirect;
	t_token		*token;
	char		redir;

	words = NULL;
	redirect = NULL;
	while (*tokens && !is_token_boundary((t_token *)((*tokens)->content)))
	{
		token = (t_token *)((*tokens)->content);
		if (token->type == STR_TOKEN)
		{
			if (token->content)
				words = make_word_list(token->content, words);
		}
		else
		{
			*tokens = (*tokens)->next;
			redir = token->type;
			token = (t_token *)((*tokens)->content);
			redirect = make_redirection(token->content, select_instruction(redir), redirect);
		}
		*tokens = (*tokens)->next;
	}
	return (make_simple_command(words, redirect));
}
