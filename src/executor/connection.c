/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:50:00 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/24 12:58:29 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"
#include <unistd.h>

static int	execute_pipeline(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	t_command	*cmd;
	int			prev;
	int			exec_result;
	int			fildes[2];

	prev = pipe_in;
	cmd = command;
	while (cmd && cmd->type == cm_connection && (t_connection *)cmd->value
		&& ((t_connection *)cmd->value)->connector == '|')
	{
		if (pipe(fildes) < 0)
		{
			g_last_exit_value = EXECUTION_FAILURE;
			return (EXECUTION_FAILURE);
		}
		fd_to_close = fildes[0];
		execute_command(((t_connection *)cmd->value)->first, prev, fildes[1],
			fd_to_close);
		if (prev >= 0)
			close(prev);
		prev = fildes[0];
		close(fildes[1]);
		cmd = ((t_connection *)cmd->value)->second;
	}
	exec_result = execute_command(cmd, prev, pipe_out, 0);
	if (prev >= 0)
		close(prev);
	return (exec_result);
}

int	execute_connection(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	int				exec_result;
	t_connection	*connect;

	connect = ((t_connection *)command->value);
	exec_result = EXECUTION_SUCCESS;
	if (connect->connector == '|')
		exec_result = execute_pipeline(command, pipe_in, pipe_out, fd_to_close);
	if (connect->connector == AND_AND || connect->connector == OR_OR)
	{
		exec_result = execute_command(connect->first, pipe_in, pipe_out,
				fd_to_close);
		if (((connect->connector == AND_AND)
				&& (exec_result == EXECUTION_SUCCESS))
			|| ((connect->connector == OR_OR)
				&& (exec_result != EXECUTION_SUCCESS)))
			exec_result = execute_command(connect->second, pipe_in, pipe_out,
					fd_to_close);
	}
	return (exec_result);
}