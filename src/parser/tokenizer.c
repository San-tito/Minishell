/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_utils.h"

static void	check_boundary(char **word, t_token_range *token_rng,
		t_list **tokens, t_list **words)
{
	char	update;

	if (**word == ' ' || **word == '\0')
		update = handle_str(token_rng, tokens, words);
	else if (**word == '(')
		update = handle_parentheses(token_rng, tokens, words, OPEN_PAR_TOKEN);
	else if (**word == ')')
		update = handle_parentheses(token_rng, tokens, words, CLOSE_PAR_TOKEN);
	else if (**word == '&')
		update = handle_and(token_rng, tokens, words, *(*word + 1) == '&');
	else if (**word == '|')
		update = handle_or(token_rng, tokens, words, *(*word + 1) == '|');
	else if (**word == '<')
		update = handle_in(token_rng, tokens, words, *(*word + 1) == '<');
	else if (**word == '>')
		update = handle_out(token_rng, tokens, words, *(*word + 1) == '>');
	else 
	{
		(*word)++;
		(token_rng->len)++;
		return ;
	}
	*word = (*word + update);
}

static char	is_quote(char **word, t_token_range *token_range)
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

static t_token_range	init_token_range(char *word)
{
	t_token_range	token_range;

	token_range.first = word;
	token_range.len = 0;
	token_range.error = 0;
	return (token_range);
}

/*
 *	Searches a word and extracts and converts all the tokens inside of it.
 *	Add said tokens to a t_list of tokens.
 */
static char	append_tokens(char *word, t_list **tokens, t_list **words)
{
	t_token_range	token_range;

	token_range = init_token_range(word);
	while (*word)
	{
		if (!is_quote(&word, &token_range))
		{
			check_boundary(&word, &token_range, tokens, words);
			if (token_range.error)
				return (0);
		}
		else
		{
			word++;
			token_range.len++;
		}
	}
	check_boundary(&word, &token_range, tokens, words);
	return (!token_range.error);
}

/*
 *	Converts words into tokens.
 */
t_list	*tokenizer(t_list **words)
{
	t_list	*tokens;
	t_list	*lst;

	tokens = NULL;
	lst = *words;
	while (lst)
	{
		if (!append_tokens((char *)lst->content, &tokens, words))
			return (NULL);
		lst = lst->next;
	}
	return (tokens);
}
