/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/24 12:38:49 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "findcmd.h"
#include "jobs.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>

int			g_last_exit_value;
int			already_forked;

static void	close_pipes(int in, int out)
{
	if (in >= 0)
		close(in);
	if (out >= 0)
		close(out);
}

static void	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != NO_PIPE)
	{
		if (dup2(pipe_in, 0) < 0)
			internal_error("cannot duplicate fd %d to fd %d", pipe_in, 0);
		if (pipe_in > 0)
			close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		if (dup2(pipe_out, 1) < 0)
			internal_error("cannot duplicate fd %d to fd %d", pipe_out, 1);
		if (pipe_out == 0 || pipe_out > 1)
			close(pipe_out);
	}
}

int	shell_execve(const char *command, char **args, char **env)
{
	int	errnum;

	g_last_exit_value = 0;
	execve(command, args, env);
	errnum = errno;
	if (errnum != ENOEXEC)
	{
		g_last_exit_value = EX_NOEXEC;
		if (errnum == ENOENT)
			g_last_exit_value = EX_NOTFOUND;
		if (file_status(command) & FS_DIRECTORY)
			internal_error("%s: %s", command, strerror(EISDIR));
		else
			internal_error("%s: %s", command, strerror(errnum));
	}
	return (g_last_exit_value);
}

static int	execute_builtin(t_builtin_func *builtin, t_word_list *words,
		t_redirect *redirects)
{
	int	result;

	if (redirects && (do_redirections(redirects) != 0))
		return (EXECUTION_FAILURE);
	result = ((*builtin)(words->next));
	return (result);
}

static int	execute_disk_command(t_simple_com *simple, int pipe_in,
		int pipe_out)
{
	pid_t		pid;
	char		**args;
	const char	*pathname = simple->words->word;
	const char	*command = search_for_command(pathname);

	if (command)
		update_env("_=", command);
	if (already_forked && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
		pid = 0;
	else
		pid = make_child();
	if (pid == 0)
	{
		do_piping(pipe_in, pipe_out);
		if (simple->redirects && (do_redirections(simple->redirects) != 0))
			exit(EXECUTION_FAILURE);
		if (command == 0)
		{
			internal_error("%s: command not found", pathname);
			exit(EX_NOTFOUND);
		}
		args = wlist_to_carray(simple->words);
		exit(shell_execve(command, args, environ));
	}
	close_pipes(pipe_in, pipe_out);
	sh_free((void *)command);
	return (EXECUTION_SUCCESS);
}

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

static int	execute_connection(t_command *command, int pipe_in, int pipe_out,
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

static int	execute_simple_command(t_simple_com *simple, int pipe_in,
		int pipe_out, int fd_to_close)
{
	t_builtin_func	*builtin;
	int				result;
	char			*this_command_name;

	result = EXECUTION_SUCCESS;
	this_command_name = simple->words->word;
	already_forked = 0;
	builtin = find_builtin(this_command_name);
	if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
	{
		if (make_child() == 0)
		{
			if (fd_to_close)
				close(fd_to_close);
			already_forked = 1;
			do_piping(pipe_in, pipe_out);
			pipe_in = pipe_out = NO_PIPE;
		}
		else
		{
			if (pipe_out != NO_PIPE)
				result = g_last_exit_value;
			close_pipes(pipe_in, pipe_out);
			return (result);
		}
	}
	if (builtin)
	{
		if (already_forked)
		{
			exit(execute_builtin(builtin, simple->words, simple->redirects));
		}
		result = execute_builtin(builtin, simple->words, simple->redirects);
	}
	else
		result = execute_disk_command(simple, pipe_in, pipe_out);
	return (result);
}

int	execute_command(t_command *command, int pipe_in, int pipe_out,
		int fd_to_close)
{
	int	exec_result;

	if (command == 0)
		return (EXECUTION_SUCCESS);
	exec_result = EXECUTION_SUCCESS;
	if (command->type == cm_simple)
	{
		exec_result = execute_simple_command((t_simple_com *)command->value,
				pipe_in, pipe_out, fd_to_close);
		if (pipe_out == NO_PIPE)
			exec_result = waitchld(-1);
	}
	else if (command->type == cm_connection)
		exec_result = execute_connection(command, pipe_in, pipe_out,
				fd_to_close);
	g_last_exit_value = exec_result;
	return (g_last_exit_value);
}
