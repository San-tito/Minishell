/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
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

	if (token_range->len != 0)
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

static char	manage_str(t_token_range *token_range, t_list **tokens, t_list **words)
{
	create_str_token(token_range, tokens, words);
	return (0);
}

static char	manage_parentheses(t_token_range *token_range, t_list **tokens, t_list **words, char TOKEN)
{
	t_token	*token;
	t_list	*node;

	create_str_token(token_range, tokens, words);
	token = new_token(TOKEN, NULL);
	if (token == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	return (1);
}

static char	manage_and(t_token_range *token_range, t_list **tokens, t_list **words, char *word)
{
	t_token	*token;
	t_list	*node;

	if (*(word + 1) != '&')
		handle_error(words, tokens, AND_ERROR);
	create_str_token(token_range, tokens, words);
	token = new_token(AND_TOKEN, NULL);
	if (token == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	return (2);
}

static char	manage_or(t_token_range *token_range, t_list **tokens, t_list **words, char *word)
{
	char	token_type;
	t_token	*token;
	t_list	*node;

	create_str_token(token_range, tokens, words);
	if (*(word + 1) == '|')
		token_type = OR_TOKEN;
	else
		token_type = PIPE_TOKEN;
	token = new_token(token_type, NULL);
	if (token == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	if (token_type == OR_TOKEN)
		return (2);
	return (1);
}

static char	manage_in(t_token_range *token_range, t_list **tokens, t_list **words, char *word)
{
	char	token_type;
	t_token	*token;
	t_list	*node;

	create_str_token(token_range, tokens, words);
	if (*(word + 1) == '<')
		token_type = HEREDOC_TOKEN;
	else
		token_type = INPUT_TOKEN;
	token = new_token(token_type, NULL);
	if (token == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	if (token_type == HEREDOC_TOKEN)
		return (2);
	return (1);
}

static char	manage_out(t_token_range *token_range, t_list **tokens, t_list **words, char *word)
{
	char	token_type;
	t_token	*token;
	t_list	*node;

	create_str_token(token_range, tokens, words);
	if (*(word + 1) == '>')
		token_type = APPEND_TOKEN;
	else
		token_type = OUTPUT_TOKEN;
	token = new_token(token_type, NULL);
	if (token == NULL)
		handle_error(words, tokens, MALLOC_ERROR);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		handle_error(words, tokens, MALLOC_ERROR);
	}
	if (token_type == APPEND_TOKEN)
		return (2);
	return (1);
}

void	is_boundary(char **word, t_token_range *token_range, t_list **tokens, t_list **words)
{
	char	update_value;

	update_value = 0;
	if (**word == ' ' || **word == '\0')
		update_value = manage_str(token_range, tokens, words);
	else if (**word == '(')
		update_value = manage_parentheses(token_range, tokens, words, OPEN_PARENTHESIS_TOKEN);
	else if (**word == ')')
		update_value = manage_parentheses(token_range, tokens, words, CLOSE_PARENTHESIS_TOKEN);
	else if (**word == '&')
		update_value = manage_and(token_range, tokens, words, *word);
	else if (**word == '|')
		update_value = manage_or(token_range, tokens, words, *word);
	else if (**word == '<')
		update_value = manage_in(token_range, tokens, words, *word);
	else if (**word == '>')
		update_value = manage_out(token_range, tokens, words, *word);
	*word = (*word + update_value);
}
