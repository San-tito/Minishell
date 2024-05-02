/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

static char	*get_error_msg(char token_type)
{
	if (token_type == AND_TOKEN)
		return (AND_BOUNDARY_ERROR);
	else if (token_type == PIPE_TOKEN)
		return (PIPE_BOUNDARY_ERROR);
	else if (token_type == OR_TOKEN)
		return (OR_BOUNDARY_ERROR);
	else if (token_type == HEREDOC_TOKEN)
		return (HEREDOC_BOUNDARY_ERROR);
	return (APPEND_BOUNDARY_ERROR);
}

static char	check_adjacents(t_list **tokens)
{
	t_token	*token;
	char	last_token_type;
	t_list	*lst;

	lst = *tokens;
	last_token_type = ((t_token *)(lst->content))->type;
	lst = lst->next;
	while (lst != NULL)
	{
		token = (t_token *)(lst->content);
		if (last_token_type > CLOSE_PAR_TOKEN && token->type > CLOSE_PAR_TOKEN && token->type < INPUT_TOKEN)
			return (handle_checker_error(tokens, get_error_msg(last_token_type)));
		last_token_type = token->type;
		lst = lst->next;
	}
	if (last_token_type > CLOSE_PAR_TOKEN)
		return (handle_checker_error(tokens, NEWLINE_BOUNDARY_ERROR));
	return (1);
}

static char	check_heredocs(t_list **tokens)
{
	t_list	*lst;
	int		n_heredoc;

	lst = *tokens;
	n_heredoc = 0;
	while (lst)
	{
		if (((t_token *)(lst->content))->type == HEREDOC_TOKEN)
		{
			n_heredoc++;
			if (n_heredoc >= MAX_HEREDOC)
				return (handle_token_error(tokens, MAX_HEREDOC_ERROR));
		}
		lst = lst->next;
	}
	return (1);
}

/*
 *	Checks that the boundaries of the tokens are correct.
 *	Returns 0 if there is an error.
 */
char	check_tokens(t_list **tokens)
{
	if (*tokens == NULL)
		return (1);

	//check that at least there is one STR_TOKEN
	//not sure if needed

	//check that all open par are closed, and that there is always one par opened and before one closes
	check_parentheses(tokens);

	//check that no two | or || or && or ( or ) are together with others of this or same 
	if (!check_adjacents(tokens))
		return (0);

	//check heredocs (MAX_HEREDOC: 16 [in bash])
	if (!check_heredocs(tokens))
		return (0);
	return (1);
}
