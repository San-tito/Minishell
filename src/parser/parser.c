/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 13:11:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

t_command	*parse_command(char *job)
{
	t_list		*tokens;
	t_list		*tokens_init;
	t_command	*command;

	if (job == NULL || *job == '\0')
		return (NULL);
	tokens = lexer(job);
	if (tokens == NULL)
		return (NULL);
	handle_heredocs(&tokens); //to fix
	//expansor(&tokens);
	tokens_init = tokens;
	//maybe print malloc error if command == NULL
	command = parse_tokens(&tokens);
	ft_lstclear(&tokens_init, NULL);
	return (command);
}
