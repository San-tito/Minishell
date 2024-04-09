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

#include "check_tokens.h"

static void	check_parentheses(t_list **tokens)
{
	t_check_par	check_par;
	t_token		*token;

	check_par.parentesis_used = 0;
	check_par.lst = *tokens;
	while (check_par.lst != NULL)
	{
		token = (t_token *)(check_par.lst->content);
		if (token->type == CLOSE_PARENTHESIS_TOKEN)
			if(check_par.parentesis_used == 0)
				handle_token_error(tokens, CLOSED_PARENTESIS_ERROR);
			else
				check_par.parentesis_used--;
		else if (token->type == OPEN_PARENTHESIS_TOKEN)
			check_par.parentesis_used++;
		check_par.lst = check_par.lst->next;
	}
	if(check_par.parentesis_used != 0)
		handle_token_error(tokens, PARENTESIS_NOT_CLOSED_ERROR);
}

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

static void	check_adjacents(t_list **tokens)
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
		if (last_token_type > CLOSE_PARENTHESIS_TOKEN && token->type > CLOSE_PARENTHESIS_TOKEN)
			handle_token_error(tokens, get_error_msg(last_token_type));
		last_token_type = token->type;
		lst = lst->next;
	}
	if (last_token_type > CLOSE_PARENTHESIS_TOKEN)
		handle_token_error(tokens, NEWLINE_BOUNDARY_ERROR);
}

void	check_tokens(t_list **tokens)
{
	if (*tokens == NULL)
		return ;

	//check that at least there is one STR_TOKEN
	//not sure if needed

	//check that all open par are closed, and that there is always one par opened and before one closes
	check_parentheses(tokens);

	//check that no two | or || or && or ( or ) are together with others of this or same 
	check_adjacents(tokens);
}
