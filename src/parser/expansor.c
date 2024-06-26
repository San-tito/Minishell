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

static char	can_expand_env_var(char *content, t_content_data *content_data)
{
	if (*content == '\'' && !content_data->double_q)
		content_data->single_q = !content_data->single_q;
	else if (*content == '\"' && !content_data->single_q)
		content_data->double_q = !content_data->double_q;
	else if (content_data->single_q)
		return (0);
	else if (*content != '$')
		return (0);
	else if (content_data->double_q && *(content + 1) == '\"')
		return (0);
	else if (*(content + 1) == ' ' || *(content + 1) == '\0')
		return (0);
	else
		return (1);
	return (0);
}

/*
 *	Iterates the content of a token searching the start of an environment
 *	variable ($) without being in single quotes.
 *	Once it finds it, it expands it.
 */
static char	search_environment_variables(t_token *token,
	t_list **environment_vars)
{
	char			*content;
	t_content_data	content_data;
	char			expanded;

	content_data.start = token->content;
	content_data.len = 0;
	content_data.single_q = 0;
	content_data.double_q = 0;
	content = token->content;
	expanded = NOT_EXPANDED;
	while (*content)
	{
		if (can_expand_env_var(content, &content_data))
		{
			expand_env_var(&content, &content_data, environment_vars);
			expanded = EXPANDED;
		}
		else
		{
			content++;
			content_data.len++;
		}
	}
	append_last_chars(environment_vars, content_data, expanded);
	return (expanded);
}

/*
 *	Searches STR_TOKENs that may contain environmental variables.
 *	If the content of the token contained an environmental variable,
 *	it returns a t_list with the updated content.
 *	This new t_list must be inserted into tokens and must swap the token
 *	that was searched.
 */
static void	expand_environment_variables(t_list **tokens, t_list **new_tokens)
{
	t_list	*new_list;
	t_list	*node;
	t_token	*token;

	if (*tokens == NULL)
		return ;
	token = (t_token *)((*tokens)->content);
	node = *tokens;
	*tokens = (*tokens)->next;
	node->next = NULL;
	if (token->type == STR_TOKEN && token->content != NULL)
	{
		new_list = NULL;
		if (search_environment_variables(token, &new_list) == EXPANDED)
		{
			ft_lstadd_back(new_tokens, new_list);
			ft_lstdelone(node, del_token);
			expand_environment_variables(tokens, new_tokens);
			return ;
		}
	}
	ft_lstadd_back(new_tokens, node);
	expand_environment_variables(tokens, new_tokens);
}

/*
 * 	First it expands the environment variables and then
 *	it expands the wildcards (environment variables can have * inside of them)
 */
void	expansor(t_list **tokens)
{
	t_list	*new_tokens;

	new_tokens = NULL;
	expand_environment_variables(tokens, &new_tokens);
	*tokens = new_tokens;
	//expand_wildcards(tokens);
}
