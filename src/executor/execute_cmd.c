/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/02 12:45:14 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "jobs.h"
#include "minishell.h"

int	g_last_exit_value;

int	execute_command(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	pid_t	last_made_pid;
	int		exec_result;

	if (command == 0)
		return (EXECUTION_SUCCESS);
	exec_result = EXECUTION_SUCCESS;
	if (command->type == cm_simple)
	{
		last_made_pid = NO_PID;
		exec_result = execute_simple_command((t_simple_com *)command->value,
				pipe_in, pipe_out, &last_made_pid, fd_to_close);
		if (last_made_pid != NO_PID && pipe_out == NO_PIPE)
			exec_result = waitchld(last_made_pid);
	}
	else if (command->type == cm_connection)
		exec_result = execute_connection(command, pipe_in, pipe_out,
				fd_to_close);
	g_last_exit_value = exec_result;
	return (g_last_exit_value);
}
