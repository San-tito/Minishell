/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer(char *job, t_list **tokens)
{
	t_list	*words;

	words = separate_words(job);
	remove_empty_words(&words);
	*tokens = tokenize(words);
	//clear_words

	//	remove_quotes(words);
	//*tokens = tokenize(words);
	//clear_words(&words);
	//check_tokens(tokens);
}
