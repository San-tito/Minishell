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
	t_command	*command;

	if (*current_line == '\0')
		return (NULL);
	tokens = lexer(current_line);
	if (tokens == NULL)
		return (NULL);
    // El malloc no puede fallar, si falla exit(2) <- POSIX; controlado en sh_malloc
	// <<Malloc error printeado en sh_malloc>> maybe print malloc error if command == NULL
	command = parse_tokens(&tokens);
	return (command);
}
