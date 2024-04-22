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

static char	handle_boundary(char **word, t_token_range *token_range, t_list **tokens, t_list **words)
{
	char	update_value;

	if (**word == ' ' || **word == '\0')
		update_value = handle_str(token_range, tokens, words);
	else if (**word == '(')
		update_value = handle_parentheses(token_range, tokens, words, OPEN_PARENTHESIS_TOKEN);
	else if (**word == ')')
		update_value = handle_parentheses(token_range, tokens, words, CLOSE_PARENTHESIS_TOKEN);
	else if (**word == '&')
		update_value = handle_and(token_range, tokens, words, *(*word + 1) == '&');
	else if (**word == '|')
		update_value = handle_or(token_range, tokens, words, *(*word + 1) == '|');
	else if (**word == '<')
		update_value = handle_in(token_range, tokens, words, *(*word + 1) == '<');
	else if (**word == '>')
		update_value = handle_out(token_range, tokens, words, *(*word + 1) == '>');
	else
		return (0);
	*word = (*word + update_value);
	return (1);
}

static char	handle_quotes(char **word, t_token_range *token_range)
{
	if (**word == '\'')
	{
		token_range->len++;
		(*word)++;
		while (**word != '\'')
		{
			token_range->len++;
			(*word)++;
		}
		return (1);
	}
	else if (**word == '\"')
	{
		token_range->len++;
		(*word)++;
		while (**word != '\"')
		{
			token_range->len++;
			(*word)++;
		}
		return (1);
	}
	return (0);
}

static void	append_tokens(char *word, t_list **tokens, t_list **words)
{
	t_token_range	token_range;

	token_range.first = word;
	token_range.len = 0;
	while (*word)
	{
		if (!handle_quotes(&word, &token_range))
		{
			if (!handle_boundary(&word, &token_range, tokens, words))
			{
				word++;
				token_range.len++;
			}
		}
		else
		{
			word++;
			token_range.len++;
		}
	}
	handle_boundary(&word, &token_range, tokens, words);
}

t_list	*tokenizer(t_list **words)
{
	t_list	*tokens;
	t_list	*lst;

	tokens = NULL;
	lst = *words;
	while (lst)
	{
		append_tokens((char *)lst->content, &tokens, words);
		lst = lst->next;
	}
	return (tokens);
}
