/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_tokens_".c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_tokens.h"

static void	check_parentheses_closure(t_list **tokens)
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
static void	check_parentheses_boundaries(t_list **tokens)
{
	t_list	*lst;
	char	last_token_type;
	t_token	*token;

	last_token_type = -1;
	lst = *tokens;
	while (lst)
	{
		token = (t_token*)(lst->content);
		if (token->type == OPEN_PARENTHESIS_TOKEN)
		{
			if (!((last_token_type >= AND_TOKEN && last_token_type <= OR_TOKEN) || last_token_type == OPEN_PARENTHESIS_TOKEN || last_token_type == -1))
				handle_token_error(tokens, OPEN_PARENTHESIS_BOUNDARY_ERROR);
			if (lst->next != NULL)
			{
				
			}
		}
		else if (token->type == CLOSE_PARENTHESIS_TOKEN)
		{

		}
		last_token_type = token->type;
		lst = lst->next;
	}
}

void	check_parentheses(t_list **tokens)
{
	check_parentheses_closure(tokens);

	//check that there is always a str before each open par or another open par
	check_parentheses_boundaries(tokens);
}
