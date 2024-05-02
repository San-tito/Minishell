/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:50:00 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/02 10:35:22 by sguzman          ###   ########.fr       */
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
	int			sewer[2];

	prev = pipe_in;
	cmd = command;
	while (cmd && cmd->type == cm_connection && (t_connection *)cmd->value
		&& ((t_connection *)cmd->value)->connector == '|')
	{
		if (pipe(sewer) < 0)
			return (g_last_exit_value = EXECUTION_FAILURE);
		execute_command(((t_connection *)cmd->value)->first, prev, sewer[1],
			fd_to_close = sewer[0]);
		close_pipes(prev, NO_PIPE);
		prev = sewer[0];
		close(sewer[1]);
		cmd = ((t_connection *)cmd->value)->second;
	}
	exec_result = execute_command(cmd, prev, pipe_out, 0);
	close_pipes(prev, NO_PIPE);
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
			exec_result = execute_command(connect->second, NO_PIPE, NO_PIPE, 0);
	}
	return (exec_result);
}
