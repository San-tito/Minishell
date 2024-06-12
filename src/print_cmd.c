/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/12 18:03:36 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	print_redirection_list(t_redirect *redirects)
{
	while (redirects)
	{
		if (redirects->instruction == r_input_direction)
			ft_printf("< %s", redirects->filename);
		else if (redirects->instruction == r_output_direction)
			ft_printf("> %s", redirects->filename);
		else if (redirects->instruction == r_appending_to)
			ft_printf(">> %s", redirects->filename);
		redirects = redirects->next;
		if (redirects)
			ft_printf(" ");
	}
}

static void	print_word_list(t_word_list *list, char *separator)
{
	t_word_list	*w;

	w = list;
	while (w)
	{
		ft_printf("%s", w->word);
		w = w->next;
		if (w)
			ft_printf("%s", separator);
	}
}

void	print_simple_command(t_simple_com *simple_command)
{
	if (simple_command->words)
		print_word_list(simple_command->words, " ");
	if (simple_command->redirects)
	{
		if (simple_command->words)
			ft_printf(" ");
		print_redirection_list(simple_command->redirects);
	}
}

void	print_subshell(t_command *command)
{
	ft_printf("( ");
	print_command((t_command *)command);
	ft_printf(" )");
}

void	print_command(t_command *command)
{
	t_connection	*connect;

	if (command == 0)
		return ;
	else if (command->type == cm_simple)
		print_simple_command((t_simple_com *)command->value);
	else if (command->type == cm_connection)
	{
		connect = (t_connection *)command->value;
		print_command(connect->first);
		if (connect->connector == '|')
			ft_printf(" | ");
		else if (connect->connector == AND_AND)
			ft_printf(" && ");
		else if (connect->connector == OR_OR)
			ft_printf(" || ");
		print_command(connect->second);
	}
	else if (command->type == cm_subshell)
		print_subshell((t_command *)command->value);
}
