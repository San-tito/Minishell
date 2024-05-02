/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_utils.h"

static t_token	*new_token(char token_type, char *token_content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = token_type;
	token->content = token_content;
	return (token);
}

char	add_token(char token_type, char *data, t_list **tokens, t_list **words)
{
	t_token	*token;
	t_list	*node;

	token = new_token(token_type, data);
	if (token == NULL)
		return (handle_error(words, tokens, MALLOC_ERROR));
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		return (handle_error(words, tokens, MALLOC_ERROR));
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

void	create_str_token(t_token_range *token_range, t_list **tokens, t_list **words)
{
	char	*content;

	if (token_range->len == 0)
		return ;
	content = ft_substr(token_range->first, 0, token_range->len);
	if (content == NULL)
	{
		token_range->error = 1;
		handle_error(words, tokens, MALLOC_ERROR);
		return ;
	}
	if (!add_token(STR_TOKEN, content, tokens, words))
	{
		free(content);
		token_range->error = 1;
		return ;
	}
	token_range->first = token_range->first + token_range->len;
	token_range->len = 0;
}

char	handle_str(t_token_range *token_range, t_list **tokens, t_list **words)
{
	create_str_token(token_range, tokens, words);
	return (1);
}
