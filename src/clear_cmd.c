/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:37 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/10 13:47:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	clear_command(t_command *command)
{
	void	*c;

	if (command == 0)
		return ;
	if (command->type == cm_simple)
	{
		c = command->value;
		clear_words(((t_simple_com *)c)->words);
		clear_redirects(((t_simple_com *)c)->redirects);
		sh_free(c);
	}
	else if (command->type == cm_connection)
	{
		c = command->value;
		clear_command(((t_connection *)c)->first);
		clear_command(((t_connection *)c)->second);
		sh_free(c);
	}
	sh_free(command);
}
