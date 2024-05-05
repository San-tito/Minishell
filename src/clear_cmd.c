/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:37 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/05 20:40:31 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "sh_malloc.h"

void	clear_redirects(t_redirect *list)
{
	t_redirect	*t;

	while (list)
	{
		t = list;
		list = list->next;
		sh_free(t->filename);
	}
	sh_free(t);
}

void	clear_words(t_word_list *list)
{
	t_word_list	*t;

	while (list)
	{
		t = list;
		list = list->next;
		sh_free(t->word);
		sh_free(t);
	}
}

static void	clear_simple_command(t_simple_com *command)
{
	clear_words(command->words);
	clear_redirects(command->redirects);
	sh_free(command);
}

static void	clear_connection(t_connection *connection)
{
	clear_command(connection->first);
	clear_command(connection->second);
	sh_free(connection);
}

void	clear_command(t_command *command)
{
	t_command_type	type;

	if (command == 0)
		return ;
	type = command->type;
	if (type == cm_simple)
		clear_simple_command((t_simple_com *)(command->value));
	else if (type == cm_connection)
		clear_connection((t_connection *)(command->value));
	else if (type == cm_subshell)
	{
		clear_command((t_command *)command->value);
		sh_free(command->value);
	}
	sh_free(command);
}
