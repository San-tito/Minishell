/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/28 17:28:55 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "jobs.h"
#include "minishell.h"
#include <stdio.h>

extern pid_t	last_made_pid;
extern int		already_making_children;
int				g_last_exit_value;

int	execute_command(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	int	exec_result;

	//print_command(command);
	//printf("\nin -> %i; out -> %i\n",pipe_in,pipe_out);
	if (command == 0)
		return (EXECUTION_SUCCESS);
	exec_result = EXECUTION_SUCCESS;
	if (command->type == cm_simple)
	{
		exec_result = execute_simple_command((t_simple_com *)command->value,
				pipe_in, pipe_out, fd_to_close);
		if (already_making_children && pipe_out == NO_PIPE)
		{
			already_making_children = 0;
			if (last_made_pid != NO_PID)
				exec_result = waitchld(last_made_pid);
		}
	}
	else if (command->type == cm_connection)
		exec_result = execute_connection(command, pipe_in, pipe_out,
				fd_to_close);
	g_last_exit_value = exec_result;
	return (g_last_exit_value);
}
