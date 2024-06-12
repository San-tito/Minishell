/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_tokens_2.c                             :+:      :+:    :+:   */
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

static char	check_parentheses_closure(t_list **tokens)
{
	t_check_par	check_par;
	t_token		*token;

	check_par.parentesis_used = 0;
	check_par.lst = *tokens;
	while (check_par.lst != NULL)
	{
		token = (t_token *)(check_par.lst->content);
		if (token->type == CLOSE_PAR_TOKEN)
			if(check_par.parentesis_used == 0)
				return (handle_token_error(tokens, CLOSED_PARENTHESIS_BOUNDARY_ERROR));
			else
				check_par.parentesis_used--;
		else if (token->type == OPEN_PAR_TOKEN)
			check_par.parentesis_used++;
		check_par.lst = check_par.lst->next;
	}
	if(check_par.parentesis_used != 0)
		return (handle_token_error(tokens, PARENTESIS_NOT_CLOSED_ERROR));
	return (1);
}

/*
 *	If last token is ')' we check the validity of the following (curr_token_type). (must be |,&,||,),<,<<,>,>>.)
 *	If last token is '(' we also check the validity of the following (curr_token_type). (must be <,<<,>,>>,(,str)
 *	If current token is ')' we check the validity of the last token.
 *	If current token is '(' we also check the validity of the last token.
 */
static char	boundary_valid(char last_token_type, t_token *token)
{
	char	curr_token_type;

	curr_token_type = token->type;
	if (last_token_type == CLOSE_PAR_TOKEN)
	{
		if (curr_token_type < CLOSE_PAR_TOKEN)
			return (0);
	}
	else if (last_token_type == OPEN_PAR_TOKEN)
	{
		if (!((curr_token_type >= INPUT_TOKEN && curr_token_type <= APPEND_TOKEN) || curr_token_type <= OPEN_PAR_TOKEN))
			return (0);
	}
	if (curr_token_type == CLOSE_PAR_TOKEN)
	{
		if (!(last_token_type == CLOSE_PAR_TOKEN || last_token_type == STR_TOKEN))
			return (0);
	}
	else if (curr_token_type == OPEN_PAR_TOKEN)
	{
		if (!(last_token_type == AND_TOKEN || last_token_type == PIPE_TOKEN || last_token_type == OR_TOKEN))
			return (0);
	}
	return (1);
}

/*
 *	Checks that before an OPEN_PARENTHESIS_TOKEN there is always another OPEN_PARENTHESIS_TOKEN
 *	or a TOKEN that is: (TOKEN != TOKEN_STR && TOKEN != CLOSE_PARENTHESIS_TOKEN).
 *	Also checks that after an OPEN_PARENTHESIS_TOKEN there is always a TOKEN_STR or
 *	another OPEN_PARENTHESIS_TOKEN.
 *	Also checks that before a CLOSE_PARENTHESIS_TOKEN there is always another CLOSE_PARENTHESIS_TOKEN
 *	or a TOKEN_STR.
 *	Also checks that after a CLOSE_PARENTHESIS_TOKEN there is always another CLOSE_PARENTHESIS_TOKEN
 *	or a TOKEN that is: (TOKEN != TOKEN_STR && TOKEN != CLOSE_PARENTHESIS_TOKEN).
 */
static char	check_parentheses_boundaries(t_list **tokens)
{
	t_token	*token;
	char	last_token_type;
	t_list	*lst;

	if (*tokens == NULL)
		return (1);
	lst = *tokens;
	last_token_type = ((t_token *)(lst->content))->type;
	lst = lst->next;
	while (lst != NULL)
	{
		token = (t_token *)(lst->content);
		if (!boundary_valid(last_token_type, token))
			return (handle_checker_error(tokens, get_error_msg(token->type)));
		last_token_type = token->type;
		lst = lst->next;
	}
	return (1);
}

char	check_parentheses(t_list **tokens)
{
	if (!check_parentheses_closure(tokens))
		return (0);

	//check that there is always a str before each open par or another open par
	if (!check_parentheses_boundaries(tokens))
		return (0);
	return (1);
}
