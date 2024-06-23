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

static void	append_last_space(char **new_content, t_content_data cont_data)
{
	char	*word;

	if (cont_data.last_space != 0)
	{
		word = ft_substr(cont_data.start, 0, cont_data.last_space); //change to sh_substr
		join_and_free(new_content, &word);
	}
}

static void	convert_wildcard(char **content, char **new_content,
	t_content_data *cont_data)
{
	append_last_space(new_content, *cont_data);
	cont_data->start += cont_data->last_space;
	cont_data->len -= cont_data->last_space;
	cont_data->last_space = 0;
	expand_matches(content, new_content, cont_data);
	cont_data->start = *content;
	if (*content)
		cont_data->start++;
	cont_data->last_space = 0;
	cont_data->len = 0;
}

/*
 *	Checks if the current character in content must be interpreted: '*' case.
 *	If there is an error when interpreting, it returns ERROR.
 */
static void	interpret_content(char **content, char **new_content,
	t_content_data *cont_data)
{
	char	currchar;

	currchar = **content;
	if (currchar == '\'' && !cont_data->double_q)
		cont_data->single_q = !cont_data->single_q;
	else if (currchar == '\"' && !cont_data->single_q)
		cont_data->double_q = !cont_data->double_q;
	else
	{
		if (currchar == ' ' && !cont_data->single_q && !cont_data->double_q)
			cont_data->last_space = cont_data->len;
		else if (currchar == '*' && !cont_data->single_q
			&& !cont_data->double_q)
		{
			convert_wildcard(content, new_content, cont_data);
			return ;
		}
	}
	(*content)++;
	cont_data->len++;
}

/*
*	Searches the content of the token for wildcards
*	and expands them.
*/
static void	handle_wildcards(t_token *token)
{
	t_content_data	content_data;
	char			*content;
	char			*new_content;

	content_data = initialize_content(token->content, &content, &new_content);
	while (*content)
		interpret_content(&content, &new_content, &content_data);
	if (new_content == NULL)
		return ;
	if (content_data.last_space == 0)
	{
		free(token->content);
		token->content = new_content;
	}
	else
		finalize_content(token, &new_content, content_data);
}

/*
*	Gets a list of tokens and for each STR_TOKEN it finds
*	expands the wildcards inside of it.
*/
char	expand_wildcards(t_list **tokens)
{
	t_list	*lst;
	t_token	*token;

	lst = *tokens;
	while (lst)
	{
		token = (t_token *)(lst->content);
		if (token->type == STR_TOKEN && token->content != NULL)
			handle_wildcards(token);
		lst = lst->next;
	}
	return (CORRECT);
}
