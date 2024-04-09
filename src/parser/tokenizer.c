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

static void	obtain_tokens(char *word, t_list **tokens, t_list **words)
{
	t_token_range	token_range;

	token_range.first = word;
	token_range.len = 0;
	while (*word)
	{
		if (!handle_quotes(&word, &token_range))
		{
			if (!is_boundary(&word, &token_range, tokens, words))
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
	is_boundary(&word, &token_range, tokens, words);
}

t_list	*tokenizer(t_list **words)
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
