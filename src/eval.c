/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:10:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/23 21:02:22 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reader_loop(void)
{
	int	current_command;
	int	last_command_exit_value;

	last_command_exit_value = 0;
	while (42)
	{
		current_command = read_command();
		if (!current_command)
			break ;
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
