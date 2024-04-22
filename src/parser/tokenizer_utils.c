/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"
#include "tokenizer.h"

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

static void create_str_token(t_token_range *token_range, t_list **tokens, t_list **words)
{
	char	*content;
	t_token	*token;
	t_list	*node;

	if (token_range->len == 0)
		return ;
	content = ft_substr(token_range->first, 0, token_range->len);
	if (content == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	token = new_token(STR_TOKEN, content);
	if (token == NULL)
	{
		free(content);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(content);
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	ft_lstadd_back(tokens, node);
	token_range->first = token_range->first + token_range->len;
	token_range->len = 0;
}

static void	add_token(char token_type, t_list **tokens, t_list **words)	
{
	t_token	*token;
	t_list	*node;

	token = new_token(token_type, NULL);
	if (token == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	ft_lstadd_back(tokens, node);
}

char	handle_str(t_token_range *token_range, t_list **tokens, t_list **words)
{
	create_str_token(token_range, tokens, words);
	return (1);
}

char	handle_parentheses(t_token_range *token_range, t_list **tokens, t_list **words, char token_type)
{
	create_str_token(token_range, tokens, words);
	add_token(token_type, tokens, words);
	token_range->first++;
	return (1);
}

char	handle_and(t_token_range *token_range, t_list **tokens, t_list **words, char extended)
{
	if (!extended)
		handle_error(words, tokens, AND_ERROR);
	add_token(AND_TOKEN, tokens, words);
	token_range->first += 2;
	return (2);
}

char	handle_or(t_token_range *token_range, t_list **tokens, t_list **words, char extended)
{
	char	token_type;

	create_str_token(token_range, tokens, words);
	if (extended)
		token_type = OR_TOKEN;
	else
		token_type = PIPE_TOKEN;
	add_token(token_type, tokens, words);
	if (token_type == OR_TOKEN)
	{
		token_range->first += 2;
		return (2);
	}
	token_range->first++;
	return (1);
}

char	handle_in(t_token_range *token_range, t_list **tokens, t_list **words, char extended)
{
	char	token_type;

	create_str_token(token_range, tokens, words);
	if (extended)
		token_type = HEREDOC_TOKEN;
	else
		token_type = INPUT_TOKEN;
	add_token(token_type, tokens, words);
	if (token_type == HEREDOC_TOKEN)
	{
		token_range->first += 2;
		return (2);
	}
	token_range->first++;
	return (1);
}

char	handle_out(t_token_range *token_range, t_list **tokens, t_list **words, char extended)
{
	char	token_type;

	create_str_token(token_range, tokens, words);
	if (extended)
		token_type = APPEND_TOKEN;
	else
		token_type = OUTPUT_TOKEN;
	add_token(token_type, tokens, words);
	if (token_type == APPEND_TOKEN)
	{
		token_range->first += 2;
		return (2);
	}
	token_range->first++;
	return (1);
}
