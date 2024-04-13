/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 13:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static t_command	*create_connection(t_command *first, char connect, t_command *second)
{
	t_connection	*connection;

	connection = malloc(sizeof(t_connection));
	if (connection == NULL)
		return (NULL);
	connection->first = first;
	connection->second = second;
	connection->connector = connect;
	return (make_command(cm_connection, (void *)connection));
}

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
	//here we have the connector in *tokens
	token = (t_token*)((*tokens)->content);
	if (token == NULL)
		return (first);
	connection = token->type;
	(*tokens)++
	second = convert_tokens(tokens);
	return (create_connection(first, connection, second));
}
