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
	t_list	*tokens;

	if (job == NULL || *job == '\0')
		return (NULL);
	tokens = lexer(job);
	if (tokens == NULL)
		return (NULL);
	handle_heredocs(&tokens); //to fix
	//expansor(&tokens);
	return (parse_tokens(&tokens)); //to fix
}
