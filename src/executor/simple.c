/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:50:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/24 13:00:42 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "findcmd.h"
#include "jobs.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>

int			already_forked;

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

int	execute_simple_command(t_simple_com *simple, int pipe_in, int pipe_out,
		int fd_to_close)
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
