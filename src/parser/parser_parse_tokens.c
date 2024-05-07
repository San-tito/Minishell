/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 13:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

static t_command	*create_first_node(t_list **tokens)
{
	t_command	*first;
	t_token		*token;

	token = (t_token*)((*tokens)->content);
	if (token->type == OPEN_PAR_TOKEN)
		first = create_subshell(tokens);
	else
		first = create_simple_command(tokens);
	if (first == NULL)
		return (NULL);
	return (first);
}

static t_command	*create_second_node(t_list **tokens, t_command **first)
{
	t_command	*second;

	*tokens = (*tokens)->next;
	second = parse_tokens(tokens);
	if (second == NULL)
		clear_command(*first);
	return (second);
}

t_command	*parse_tokens(t_list **tokens)
{
	t_command	*first;
	t_command	*second;
	t_command	*connection;
	t_token		*token;
	char		connector;

	first = create_first_node(tokens);
	if (first == NULL)
		return (NULL);
	if (*tokens == NULL)
		return (first);
	token = (t_token*)((*tokens)->content);
	connector = token->type;
	second = create_second_node(tokens, &first);
	if (second == NULL)
		return (NULL);
	connection = make_connect(first, second, connector);
	if (connection == NULL)
	{
		clear_command(first);
		clear_command(second);
	}
	return (connection);
}
