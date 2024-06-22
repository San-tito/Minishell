/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 23:47:21 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "parser_utils.h"

t_command	*parse_command(char *current_line)
{
	t_list		*tokens;
	t_list		*tmp;
	t_command	*command;

	if (*current_line == '\0')
		return (sh_free(current_line), NULL);
	tokens = lexer(current_line);
	if (tokens == NULL)
		return (sh_free(current_line), g_last_exit_value = 2, NULL);
	tmp = tokens;
	command = parse_tokens(&tokens);
	clear_tokens(&tmp);
	sh_free(current_line);
	return (command);
}
