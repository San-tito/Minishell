/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/18 18:34:40 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				g_last_exit_value;
extern pid_t	last_made_pid;
extern int		already_making_children;

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

static int	shell_execve(const char *command, char **args, char **env)
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

static int	execute_disk_command(t_simple_com *simple, int pipe_in,
		int pipe_out)
{
	pid_t		pid;
	char		**args;
	const char	*pathname = simple->words->word;
	const char	*command = search_for_command(pathname);

	if (command)
		update_env("_=", command);
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
		args = strvec_from_word_list(simple->words);
		exit(shell_execve(command, args, environ));
	}
	close_pipes(pipe_in, pipe_out);
	sh_free((void *)command);
	return (EXECUTION_SUCCESS);
}

static int	execute_connection(t_connection *command)
{
	int	exec_result;

	(void)command;
	exec_result = EXECUTION_SUCCESS;
	return (exec_result);
}

static int	execute_simple_command(t_simple_com *simple_command, int pipe_in,
		int pipe_out)
{
	t_builtin_func	*builtin;
	int				result;
	char			*this_command_name;

	result = EXECUTION_SUCCESS;
	this_command_name = simple_command->words->word;
	builtin = find_builtin(this_command_name);
	if (builtin)
		result = execute_builtin(builtin, simple_command->words,
				simple_command->redirects);
	else
		result = execute_disk_command(simple_command, pipe_in, pipe_out);
	return (result);
}

int	execute_command(t_command *command, int pipe_in, int pipe_out)
{
	int	exec_result;

	if (command == 0)
		return (EXECUTION_SUCCESS);
	exec_result = EXECUTION_SUCCESS;
	if (command->type == cm_simple)
	{
		exec_result = execute_simple_command((t_simple_com *)command->value,
				pipe_in, pipe_out);
		if (already_making_children && pipe_out == NO_PIPE)
		{
			already_making_children = 0;
			if (last_made_pid != NO_PID)
				exec_result = wait_for(last_made_pid);
		}
	}
	else if (command->type == cm_connection)
		exec_result = execute_connection((t_connection *)command->value);
	g_last_exit_value = exec_result;
	return (g_last_exit_value);
}
