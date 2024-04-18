/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/18 20:50:27 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(char *token)
{
	t_command	*command;
	t_word_list	*words;
	t_redirect	*redirects;
	char		**arr;

	if (token == 0)
		return (NULL);
	words = NULL;
	arr = ft_split(token, ' ');
	if (*arr == 0)
		return (NULL);
	while (*arr)
		words = make_word_list(*arr++, words);
	redirects = NULL;
	command = make_simple_command(words, redirects);
	return (command);
}
