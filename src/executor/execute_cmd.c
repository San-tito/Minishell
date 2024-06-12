/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/12 16:45:57 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "jobs.h"
#include "minishell.h"

int			g_last_exit_value;

int	execute_in_subshell(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	pid_t	pid;

	pid = make_child();
	if (pid == 0)
	{
		g_last_exit_value = execute_command((t_command *)command->value,
				NO_PIPE, NO_PIPE, fd_to_close);
		exit(g_last_exit_value);
	}
	else
	{
		close_pipes(pipe_in, pipe_out);
		if (pipe_out != NO_PIPE)
			return (EXECUTION_SUCCESS);
		g_last_exit_value = waitchld(pid);
		return (g_last_exit_value);
	}
}

static int	execute_null_command(t_redirect *redirects, int pipe_in,
		int pipe_out)
{
	int	r;
	int	io[2];

	if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
	{
		if (make_child() == 0)
		{
			do_piping(pipe_in, pipe_out);
			if (do_redirections(redirects) == 0)
				exit(EXECUTION_SUCCESS);
			else
				exit(EXECUTION_FAILURE);
		}
		else
			return (close_pipes(pipe_in, pipe_out), EXECUTION_SUCCESS);
	}
	io[0] = dup(0);
	io[1] = dup(1);
	r = do_redirections(redirects);
	do_piping(io[0], io[1]);
	close_pipes(io[0], io[1]);
	if (r != 0)
		return (EXECUTION_FAILURE);
	else
		return (EXECUTION_SUCCESS);
}

int	execute_command(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	pid_t			last_made_pid;
	t_simple_com	*simple;
	int				exec_result;

	if (command == 0)
		return (EXECUTION_SUCCESS);
	exec_result = EXECUTION_SUCCESS;
	if (command->type == cm_subshell)
		exec_result = execute_in_subshell(command, pipe_in, pipe_out,
				fd_to_close);
	else if (command->type == cm_simple)
	{
		last_made_pid = NO_PID;
		simple = (t_simple_com *)command->value;
		if (simple->words == 0)
			return (execute_null_command(simple->redirects, pipe_in, pipe_out));
		exec_result = execute_simple_command(simple, (int[]){pipe_in, pipe_out},
				&last_made_pid, fd_to_close);
		if (pipe_out == NO_PIPE && last_made_pid != NO_PID)
			exec_result = waitchld(last_made_pid);
	}
	else if (command->type == cm_connection)
		exec_result = execute_connection(command, pipe_in, pipe_out);
	g_last_exit_value = exec_result;
	return (g_last_exit_value);
}
