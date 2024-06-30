/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/30 14:20:19 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "parser_utils.h"

t_command	*parse_command(char *current_line)
{
	t_list		*tokens;
	t_list		*tmp;
	t_command	*command;
	char		err;

	if (*current_line == '\0')
		return (NULL);
	err = 0;
	tokens = lexer(current_line, &err);
	if (err == 1)
		return (*last_exit_value() = 2, NULL);
	if (err == -1)
		return (NULL);
	tmp = tokens;
	command = parse_tokens(&tokens);
	clear_tokens(&tmp);
	return (command);
}
