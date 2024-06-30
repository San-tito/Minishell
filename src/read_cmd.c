/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 00:01:28 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/30 14:18:03 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "clear_cmd.h"
#include "execute_cmd.h"
#include "input.h"
#include "minishell.h"

int	reader_loop(void)
{
	char		*line;
	t_command	*current_command;

	while (42)
	{
		line = read_command();
		current_command = parse_command(line);
		sh_free(line);
		execute_command(current_command, NO_PIPE, NO_PIPE, 0);
		clear_command(current_command);
	}
	return (*last_exit_value());
}

char	*read_command(void)
{
	char		*line;
	const char	*prompt = get_primary_prompt();

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	else if (line == 0)
		exit_builtin(NULL);
	return (line);
}
