/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/21 16:46:39 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(char *token)
{
	t_command	*command;
	char		**arr;

	if (token == 0)
		return (NULL);
	arr = ft_split(token, ' ');
	if (*arr == 0)
		return (NULL);
	command = make_connect(make_simple_command(make_word_list("cat", NULL),
				NULL), make_simple_command(make_word_list("ls", NULL), NULL),
			'|');
	return (command);
}
