/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:30:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 15:15:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(char *token)
{
	t_command	*command;
	t_word_list	*words;
	char		**arr;

	words = NULL;
	arr = ft_split(token, ' ');
	while (*arr)
		words = make_word_list(*arr++, words);
	command = make_simple_command(words, NULL);
	return (command);
}
