/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:01:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/16 17:04:09 by sguzman          ###   ########.fr       */
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
	t_simple_com	*simple;

	simple = sh_malloc(sizeof(t_simple_com));
	simple->words = words;
	simple->redirects = redirects;
	return (make_command(cm_simple, simple));
}

t_command	*make_connect(t_command *first, t_command *second, char connector)
{
	t_connection	*connection;

	connection = sh_malloc(sizeof(t_connection));
	connection->first = first;
	connection->second = second;
	connection->connector = connector;
	return (make_command(cm_connection, (void *)connection));
}

t_word_list	*make_word_list(char *word, t_word_list *head)
{
	t_word_list	*temp;

	temp = sh_malloc(sizeof(t_word_list));
	temp->word = word;
	temp->next = NULL;
	temp = (t_word_list *)list_append((t_generic_list *)head,
			(t_generic_list *)temp);
	return (temp);
}

t_redirect	*make_redirection(char *filename, t_instruction instruction,
		t_redirect *head)
{
	t_redirect	*temp;

	temp = sh_malloc(sizeof(t_redirect));
	temp->dest = 0;
	temp->filename = filename;
	temp->instruction = instruction;
	temp->flags = 0;
	temp->next = NULL;
	if (instruction == r_output_direction)
	{
		temp->flags = O_TRUNC | O_WRONLY | O_CREAT;
		temp->dest = 1;
	}
	if (instruction == r_appending_to)
	{
		temp->flags = O_APPEND | O_WRONLY | O_CREAT;
		temp->dest = 1;
	}
	if (instruction == r_input_direction)
		temp->flags = O_RDONLY;
	if (instruction == r_reading_until)
		temp = make_here_document(temp);
	temp = (t_redirect *)list_append((t_generic_list *)head,
			(t_generic_list *)temp);
	return (temp);
}
