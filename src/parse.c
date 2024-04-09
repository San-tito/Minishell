/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/09 13:29:47 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(char *token)
{
	t_command	*command;
	t_word_list	*words;
	t_redirect	*redirects;
	char		**arr;

	words = NULL;
	arr = ft_split(token, ' ');
	while (*arr)
		words = make_word_list(*arr++, words);
	redirects = make_redirection("test.txt", r_output_direction, NULL);
	redirects = make_redirection("che.txt", r_output_direction, redirects);
	command = make_simple_command(words, redirects);
	return (command);
}
