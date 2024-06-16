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

static t_instruction	select_redir(char redirect)
{
	if (redirect == OUTPUT_TOKEN)
		return (r_output_direction);
	if (redirect == INPUT_TOKEN)
		return (r_input_direction);
	if (redirect == APPEND_TOKEN)
		return (r_appending_to);
	return (r_reading_until);
}

static char	handle_redirection(t_token *token, t_list **tokens,
	t_redirect **redirect)
{
	char		redir;

	*tokens = (*tokens)->next;
	redir = token->type;
	token = (t_token *)((*tokens)->content);
	*redirect = make_redirection(sh_strdup(token->content),
			select_redir(redir), *redirect);
	if (*redirect == NULL)
		return (INTERRUMPED);
	return (CORRECT);
}

static char	obtain_params(t_list **tokens, t_word_list **words,
	t_redirect **redirect)
{
	t_token		*token;

	while (*tokens && !is_token_boundary((t_token *)((*tokens)->content)))
	{
		token = (t_token *)((*tokens)->content);
		if (token->type == STR_TOKEN)
		{
			if (token->content)
				*words = make_word_list(sh_strdup(token->content), *words);
		}
		else if (handle_redirection(token, tokens, redirect) == INTERRUMPED)
		{
			clear_words(*words);
			return (INTERRUMPED);
		}
		*tokens = (*tokens)->next;
	}
	return (CORRECT);
}

t_command	*create_simple_command(t_list **tokens)
{
	t_word_list	*words_param;
	t_redirect	*redirect_param;

	words_param = NULL;
	redirect_param = NULL;
	if (obtain_params(tokens, &words_param, &redirect_param) == INTERRUMPED)
		return (NULL);
	return (make_simple_command(words_param, redirect_param));
}
