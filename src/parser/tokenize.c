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

static void	handle_error(t_list **words, t_list **tokens, char *error_msg)
{
	ft_printf(1, "%s", error_msg);
	clear_tokens(tokens)
	clear_words(words);
	exit(1);
}

static void	handle_quotes(char **word, int *len)
{
	if (**word == '\'')
	{
		*len++;
		(*word)++;
		while (**word != '\'')
		{
			*len++;
			(*word)++;
		}
		return (1);
	}
	else if (**word == '\"')
	{
		*len++;
		(*word)++;
		while (**word != '\"')
		{
			*len++;
			(*word)++;
		}
		return (1);
	}
	return (0);
}

static void	create_token(t_token_range *token_range, t_list **tokens, t_list **words, char token_type)
{
	char	*token;
	t_list	*node;

	if (token_type >= STR_TOKEN && token_type <= CLOSE_PARENTHESIS_TOKEN)
	{
		token = ft_substr(token_range->first, 0, token_range->len);
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
}

static void is_boundary(char **word, t_token_range *token_range, t_list **tokens, t_list **words)
{
	if (*word == ' ')
	{
		create_token(token_range, tokens, words, STR_TOKEN);
		token_range->first = (*word + 1);
		token_range->len = 0;
	}
	else if (*word == '(')
	{
		create_token(token_range, tokens, words, OPEN_PARENTHESIS_TOKEN);
		token_range->first = (*word + 1);
		token_range->len = 0;
	}
	else if (*word == ')')
	{
		create_token(token_range, tokens, words, CLOSE_PARENTHESIS_TOKEN);
		token_range->first = (*word + 1);
		token_range->len = 0;
	}
	else if (*word == '|' || *word == '&' || *word == '<' || *word == '>')
	{

	}
}

static void	obtain_tokens(char *word, t_list **tokens, t_list **words)
{
	t_token_range	token_range;

	token_range.first = *word;
	token_range.len = 0;
	while (*word)
	{
		if (!handle_quotes(&word, &token_range.len))
			is_boundary(&word, &token_range, tokens, words);
		else
		{
			token_range.len++;
			word++;
		}
	}
}

t_list	*tokenize(t_list **words)
{
	t_list	*tokens;
	t_list	*lst;

	tokens = NULL;
	lst = *words;
	while (lst)
	{
		obtain_tokens((char *)lst->content, &tokens, words);
		lst = lst->next;
	}
	return (tokens);
}
