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

static char	*get_errmsg(char token_type)
{
	if (token_type == AND_TOKEN)
		return (AND_BOUNDARY_ERROR);
	else if (token_type == PIPE_TOKEN)
		return (PIPE_BOUNDARY_ERROR);
	else if (token_type == OR_TOKEN)
		return (OR_BOUNDARY_ERROR);
	else if (token_type == HEREDOC_TOKEN)
		return (HEREDOC_BOUNDARY_ERROR);
	else if (token_type == INPUT_TOKEN)
		return (INPUT_BOUNDARY_ERROR);
	else if (token_type == OUTPUT_TOKEN)
		return (OUTPUT_BOUNDARY_ERROR);
	else if (token_type == OPEN_PAR_TOKEN)
		return (OPENPAR_BOUNDARY_ERROR);
	else if (token_type == CLOSE_PAR_TOKEN)
		return (CLOSEPAR_BOUNDARY_ERROR);
	return (APPEND_BOUNDARY_ERROR);
}

/*
 *	Checks the validity of the boundaries of the token.
 *	If token is |, ||, &&, >, <, >> or << checks if the following is a STR.
 */
static char	boundary_valid(char last_token_type, t_token *token)
{
	char	curr_token_type;

	curr_token_type = token->type;
	if (last_token_type <= APPEND_TOKEN && last_token_type >= INPUT_TOKEN
		&& curr_token_type >= AND_TOKEN)
		return (ERROR);
	else if ((last_token_type == AND_TOKEN || last_token_type == OR_TOKEN
			|| last_token_type == PIPE_TOKEN) && (curr_token_type == AND_TOKEN
			|| curr_token_type == OR_TOKEN || curr_token_type == PIPE_TOKEN))
		return (ERROR);
	else if ((last_token_type == INPUT_TOKEN || last_token_type == OUTPUT_TOKEN
			|| last_token_type == HEREDOC_TOKEN
			|| last_token_type == APPEND_TOKEN)
		&& token->content == NULL)
		return (-1);
	return (CORRECT);
}

/*
 *	Checks the validity of the tokens adjacent to each other.
 *	This DOES NOT check the validity of parenthesis.
 */
static char	check_adjacents(t_list **tokens)
{
	t_token	*token;
	char	last_token_type;
	t_list	*lst;
	int		err;

	lst = *tokens;
	last_token_type = ((t_token *)(lst->content))->type;
	if (last_token_type == PIPE_TOKEN || last_token_type == AND_TOKEN
		|| last_token_type == OR_TOKEN)
		return (handle_checker_error(tokens, get_errmsg(last_token_type)));
	lst = lst->next;
	while (lst != NULL)
	{
		token = (t_token *)(lst->content);
		err = boundary_valid(last_token_type, token);
		if (err == -1)
			return (handle_token_error(tokens, AMBIGUOUS_REDIR_ERR));
		else if (err == ERROR)
			return (handle_checker_error(tokens, get_errmsg(token->type)));
		last_token_type = token->type;
		lst = lst->next;
	}
	if (last_token_type >= AND_TOKEN)
		return (handle_checker_error(tokens, NEWLINE_BOUNDARY_ERROR));
	return (CORRECT);
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
	return (CORRECT);
}

/*
 *	Checks that the boundaries of the tokens are correct.
 *	Returns 0 if there is an error.
 */
char	check_tokens(t_list **tokens)
{
	if (*tokens == NULL)
		return (CORRECT);
	if (!check_parentheses(tokens))
		return (ERROR);
	if (!check_adjacents(tokens))
		return (ERROR);
	if (!check_heredocs(tokens))
		return (ERROR);
	return (CORRECT);
}
