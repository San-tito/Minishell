/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:37 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 17:03:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

void	clear_redirects(t_redirect *list)
{
	t_redirect	*t;

	while (list)
	{
		t = list;
		list = list->next;
		if (t->instruction == r_reading_until)
			sh_free(t->here_doc_eof);
		else
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

static void clear_simple_command(t_simple_com *command)
{
	clear_words(command->words);
	clear_redirects(command->redirects);
	sh_free(command);
}

static void clear_connection(t_connection *connection)
{
	clear_command(&(connection->first));
	clear_command(&(connection->second));
	sh_free(connection);
}

//static void clear_subshell(){}

void	clear_command(t_command **command)
{
	t_command_type	type;

	type = (*command)->type;
	if (type == cm_simple)
		clear_simple_command((t_simple_com *)((*command)->value));
	else if (type == cm_connection)
		clear_connection((t_connection *)((*command)->value));
	else
		ft_printf("clear_subshell.\n");
		//clear_subshell((t_simple_com *)((*command)->value));
	free(*command);
}
