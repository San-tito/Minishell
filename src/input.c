/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:10:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 22:48:57 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reader_loop(void)
{
	char		*line;
	t_command	*current_command;
	int			last_command_exit_value;

	current_command = NULL;
	last_command_exit_value = 0;
	while (42)
	{
		line = read_command();
		if (pid < 0)
			return ;
		else if (pid == 0)
		{
			current_command = parse_command(line);
			execute_command(current_command);
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
	}
	return (last_command_exit_value);
}

char	*read_command(void)
{
	char		*line;
	const char	*prompt = "\001\033[1;32m\002minishell>\001\033[0m\002";

	line = readline(prompt);
	return (line);
}
