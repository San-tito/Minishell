/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 13:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

t_command	*convert_tokens(t_list **tokens)
{
	t_command	*first;
	t_command	*second;
	t_token		*token;
	char		connection;

	token = (t_token*)((*tokens)->content);
	if (token->type == OPEN_PARENTHESIS_TOKEN)
		first = manage_subshell(tokens);
	else
		first = create_simple_command(tokens);
	if (*tokens == NULL)
		return (first);
	token = (t_token*)((*tokens)->content);
	connection = token->type;
	*tokens = (*tokens)->next;
	second = convert_tokens(tokens);
	return (make_connect(first, second, connection));
}
