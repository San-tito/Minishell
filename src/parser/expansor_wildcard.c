/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_utils.h"

static char	*get_pattern(char **content, t_content_data *cont_data)
{
	while (**content && !(**content == ' ' && !cont_data->single_q
			&& !cont_data->double_q))
	{
		if (**content == '\'' && !cont_data->double_q)
			cont_data->single_q = !cont_data->single_q;
		else if (**content == '\"' && !cont_data->single_q)
			cont_data->double_q = !cont_data->double_q;
		(*content)++;
		cont_data->len++;
	}
	return (sh_substr(cont_data->start, 0, cont_data->len));
}

static void	expand_wildcard(char **content, t_content_data *cont_data,
	t_list **environment_vars)
{
	char	*content_before;
	char	*pattern;

	content_before = NULL;
	if (cont_data->last_space != 0)
		content_before = sh_substr(cont_data->start, 0, cont_data->last_space);
	cont_data->start += cont_data->last_space;
	pattern = get_pattern(content, cont_data);
	cont_data->start += cont_data->len;
	cont_data->len = 0;
	cont_data->last_space = 0;
	get_matches(pattern, environment_vars);
	free(pattern);
	append_content_before(&content_before, environment_vars);
}

static char	can_expand_wildcard(char *content, t_content_data *content_data)
{
	if (*content == '\'' && !content_data->double_q)
		content_data->single_q = !content_data->single_q;
	else if (*content == '\"' && !content_data->single_q)
		content_data->double_q = !content_data->double_q;
	else if (content_data->single_q)
		return (0);
	else if (content_data->double_q)
		return (0);
	else if (*content == ' ')
	{
		content_data->last_space += content_data->len;
		content_data->len = 0;
	}
	else if (*content == '*')
		return (1);
	return (0);
}

/*
*	Searches the content of the token for wildcards
*	and expands them.
*/
static char	search_wildcard(t_token *token,
	t_list **environment_vars)
{
	char			*content;
	t_content_data	content_data;
	char			expanded;

	init_data(&content_data, token->content, &expanded);
	content = token->content;
	while (*content)
	{
		if (can_expand_wildcard(content, &content_data))
		{
			expand_wildcard(&content, &content_data, environment_vars);
			expanded = EXPANDED;
		}
		else
		{
			content++;
			content_data.len++;
		}
	}
	//append_last_chars(environment_vars, content_data, expanded);
	return (expanded);
}

/*
 *	For each STR_TOKEN it finds, searches for a wildcard and creates
 *	a t_list of STR_TOKENs.
 *	If a t_list is created, it swaps the t_list for the initial STR_TOKEN.
 */
void	expand_wildcards(t_list **tokens, t_list **new_tokens)
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
		if (search_wildcard(token, &new_list) == EXPANDED)
		{
			ft_lstadd_back(new_tokens, new_list);
			ft_lstdelone(node, del_token);
			expand_wildcards(tokens, new_tokens);
			return ;
		}
	}
	ft_lstadd_back(new_tokens, node);
	expand_wildcards(tokens, new_tokens);
}
