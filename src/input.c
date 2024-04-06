/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:10:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/24 00:08:46 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reader_loop(void)
{
	t_command	*current_command;
	int			EOF_Reached;
	int			last_command_exit_value;

	current_command = (t_command *)NULL;
	EOF_Reached = 0;
	last_command_exit_value = 0;
	while (EOF_Reached == 0)
	{
		/* if (code == EXITBLTIN)
		{
			current_command = (COMMAND *)NULL;
			EOF_Reached = EOF;
		} */
		if (read_command())
		{
			execute_command(current_command);
		}
	}
	return (last_command_exit_value);
}

int	read_command(void)
{
	char		*line;
	const char	*prompt = "\001\033[1;32m\002minishell>\001\033[0m\002 ";

	line = readline(prompt);
	if (!line)
		return (0);
	parse(line);
	return (*line);
}
