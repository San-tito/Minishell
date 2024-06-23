/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_utils.h"

t_content_data	initialize_content(char *token_content, char **content,
	char **new_content)
{
	t_content_data	content_data;

	*content = token_content;
	*new_content = NULL;
	content_data.start = token_content;
	content_data.last_space = 0;
	content_data.len = 0;
	content_data.single_q = 0;
	content_data.double_q = 0;
	return (content_data);
}

static char	need_expand(char **content, t_content_data *content_data)
{
	char	next_char;

	if (content_data->single_q)
		return (0);
	if (**content != '$')
		return (0);
	next_char = *(*(content) + 1);
	if (content_data->double_q && next_char == '\"')
		return (0);
	if (next_char == ' ')
		return (0);
	if (next_char == '\0')
		return (0);
	return (1);
}

/*
 *	Checks if the current character in content must be interpreted: '$' case.
 *	If it is not, it returns not interpreted (0).
 *	If there is an error when interpreting, it returns ERROR.
 *	If there is not an error when intrepreting, it returns interpreted (1);
 */
static char	interpret_content(char **content, char **new_content,
	t_content_data *content_data)
{
	if (**content == '\'' && !content_data->double_q)
		content_data->single_q = !content_data->single_q;
	else if (**content == '\"' && !content_data->single_q)
		content_data->double_q = !content_data->double_q;
	else
	{
		if (need_expand(content, content_data))
		{
			if (append_content(new_content, *content_data) == ERROR)
				return (ERROR);
			content_data->len = 0;
			if (expand_value(new_content, content) == ERROR)
				return (ERROR);
			content_data->start = *content;
			return (1);
		}
	}
	return (0);
}

/*
*	Searches the content of the token for environmental variables
*	and expands them.
*/
static char	expand_content(t_token *token)
{
	t_content_data	content_data;
	char			*content;
	char			*new_content;
	char			interpreted;

	content_data = initialize_content(token->content, &content, &new_content);
	while (*content)
	{
		interpreted = interpret_content(&content, &new_content, &content_data);
		if (interpreted == ERROR)
			return (ERROR);
		else if (!interpreted)
		{
			content++;
			content_data.len++;
		}
	}
	if (finalize_content(token, &new_content, content_data) == ERROR)
		return (ERROR);
	return (CORRECT);
}

/*
*	Gets a list of tokens and for each STR_TOKEN it finds
*	expands the ENV values inside the content of the token.
*/
char	expansor(t_list **tokens)
{
	t_list	*lst;
	t_token	*token;

	expand_wildcards(tokens);
	lst = *tokens;
	while (lst)
	{
		token = (t_token *)(lst->content);
		if (token->type == STR_TOKEN && token->content != NULL)
		{
			if (expand_content(token) == ERROR)
				return (handle_token_error(tokens, MALLOC_ERROR));
		}
		lst = lst->next;
	}
	return (CORRECT);
}
