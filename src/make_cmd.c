/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:01:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 12:57:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*make_command(t_command_type type, void *pointer)
{
	t_command	*temp;

	temp = sh_malloc(sizeof(t_command));
	temp->type = type;
	temp->value = pointer;
	return (temp);
}

t_command	*make_simple_command(t_word_list *words, t_redirect *redirects)
{
	t_command		*command;
	t_simple_com	*simple;

	simple = sh_malloc(sizeof(t_simple_com));
	simple->words = words;
	simple->redirects = redirects;
	command = make_command(cm_simple, simple);
	return (command);
}

t_word_list	*make_word_list(char *word, t_word_list *head)
{
	t_word_list	*temp;

	temp = sh_malloc(sizeof(t_word_list));
	temp->word = word;
	temp->next = NULL;
	list_append((t_generic_list *)head, (t_generic_list *)temp);
	return (temp);
}
