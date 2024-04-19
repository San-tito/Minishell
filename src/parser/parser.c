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

#include "minishell.h"
#include "parser.h"

t_command	*parser(char *job)
{
	t_list	*tokens;

	if (job == NULL || *job == '\0')
		return (NULL);
	tokens = NULL;
	lexer(job, &tokens);
	handle_heredocs(&tokens);
	//expansor(&tokens);
	return (convert_tokens(&tokens));
}
