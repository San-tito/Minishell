/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_utils.h"

static void	count_quotes(char *str, t_handle_quotes *handle_quotes)
{
	handle_quotes->single_quotes = 0;
	handle_quotes->double_quotes = 0;
	handle_quotes->num = 0;
	while (*str)
	{
		if (*str == '\'' && !handle_quotes->double_quotes)
		{
			if (handle_quotes->single_quotes)
				handle_quotes->single_quotes = 0;
			else
				handle_quotes->single_quotes = 1;
			handle_quotes->num++;
		}
		else if (*str == '\"' && !handle_quotes->single_quotes)
		{
			if (handle_quotes->double_quotes)
				handle_quotes->double_quotes = 0;
			else
				handle_quotes->double_quotes = 1;
			handle_quotes->num++;
		}
		str++;
	}
}

static void	copy_without_quotes(char *q_str, char *unq_str,
	t_handle_quotes handle_quotes)
{
	handle_quotes.num = 0;
	while (*q_str)
	{
		if (*q_str == '\'' && !handle_quotes.double_quotes)
		{
			if (handle_quotes.single_quotes)
				handle_quotes.single_quotes = 0;
			else
				handle_quotes.single_quotes = 1;
		}
		else if (*q_str == '\"' && !handle_quotes.single_quotes)
		{
			if (handle_quotes.double_quotes)
				handle_quotes.double_quotes = 0;
			else
				handle_quotes.double_quotes = 1;
		}
		else
		{
			*(unq_str + handle_quotes.num) = *q_str;
			(handle_quotes.num)++;
		}
		q_str++;
	}
	*(unq_str + handle_quotes.num) = '\0';
}

static void	manage_quotes(t_token *token)
{
	t_handle_quotes	handle_quotes;
	char			*quoted_str;
	char			*unquoted_str;

	if (token->type != STR_TOKEN)
		return ;
	quoted_str = token->content;
	if (quoted_str == NULL)
		return ;
	count_quotes(quoted_str, &handle_quotes);
	unquoted_str = sh_malloc(sizeof(char)
			* ((ft_strlen(quoted_str) - handle_quotes.num) + 1));
	copy_without_quotes(quoted_str, unquoted_str, handle_quotes);
	free(token->content);
	token->content = unquoted_str;
}

void	remove_quotes(t_list **tokens)
{
	t_list	*lst;

	lst = *tokens;
	while (lst != NULL)
	{
		manage_quotes((t_token *)lst->content);
		lst = lst->next;
	}
}
