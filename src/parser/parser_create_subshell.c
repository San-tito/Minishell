/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create_subshell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 13:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "minishell.h"

/*
 *	Will enter only when tokens is '('.
 */
t_command	*create_subshell(t_list **tokens)
{
	t_command	*command;

	*tokens = (*tokens)->next;
	command = parse_tokens(tokens);
	if (command == NULL)
		return (NULL);
	*tokens = (*tokens)->next;
	return (make_command(cm_subshell, (void *)command));
}
