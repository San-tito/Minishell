/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 00:01:28 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/21 18:32:04 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "input.h"
#include "minishell.h"

int	reader_loop(void)
{
	char		*line;
	t_command	*current_command;

	current_command = NULL;
	while (42)
	{
		line = read_command();
		current_command = parse_command(line);
		execute_command(current_command, NO_PIPE, NO_PIPE);
	}
	return (g_last_exit_value);
}

char	*read_command(void)
{
	char		*line;
	const char	*prompt = get_primary_prompt();

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}
