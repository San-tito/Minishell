/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/10 12:56:43 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

t_command	*parse_command(char *current_line)
{
	t_list		*tokens;
	t_list		*tmp;
	t_command	*command;

	if (*current_line == '\0')
		return (NULL);
	tokens = lexer(current_line);
	if (tokens == NULL)
		return (NULL);
	tmp = tokens;
	command = parse_tokens(&tokens);
	clear_tokens(&tmp);
	return (command);
}
