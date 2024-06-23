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
#include "sh_malloc.h"

static t_token	*new_token(char token_type, char *token_content)
{
	t_token	*token;

	token = sh_malloc(sizeof(t_token));
	token->type = token_type;
	token->content = token_content;
	return (token);
}

void	add_token(char token_type, char *data, t_list **tokens)
{
	t_token	*token;
	t_list	*node;

	token = new_token(token_type, data);
	node = sh_lstnew(token);
	ft_lstadd_back(tokens, node);
}

void	create_str_token(t_token_range *token_range,
	t_list **tokens)
{
	char	*content;

	if (token_range->len == 0)
		return ;
	content = sh_substr(token_range->first, 0, token_range->len);
	add_token(STR_TOKEN, content, tokens);
	token_range->first = token_range->first + token_range->len;
	token_range->len = 0;
}

char	handle_str(t_token_range *token_range, t_list **tokens)
{
	create_str_token(token_range, tokens);
	return (1);
}
