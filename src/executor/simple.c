/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:50:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/28 15:42:52 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "findcmd.h"
#include "jobs.h"
#include "minishell.h"
#include <errno.h>
#include <string.h>

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

static int	execute_subshell_builtin(t_builtin_func *builtin,
		t_word_list *words, t_redirect *redirects)
{
	int	result;

	if (redirects && (do_redirections(redirects) != 0))
		exit(EXECUTION_FAILURE);
	result = ((*builtin)(words->next));
	exit(result);
}

static int	execute_builtin(t_builtin_func *builtin, t_word_list *words,
		t_redirect *redirects)
{
	int			result;
	const int	in = dup(0);
	const int	out = dup(1);

	if (redirects && (do_redirections(redirects) != 0))
		return (EXECUTION_FAILURE);
	result = ((*builtin)(words->next));
	do_piping(in, out);
	close_pipes(in, out);
	return (result);
}

static int	execute_disk_command(t_simple_com *simple, int pipe_in,
		int pipe_out, int fd_to_close, int nofork)
{
	int			result;
	pid_t		pid;
	char		**args;
	const char	*pathname = simple->words->word;
	const char	*command = search_for_command(pathname);

	result = EXECUTION_SUCCESS;
	if (command)
		update_env("_=", command);
	if (nofork && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
		pid = 0;
	else
		pid = make_child();
	if (pid == 0)
	{
		if (fd_to_close)
		{
			close(fd_to_close);
			fd_to_close = 0;
		}
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
	return (result);
}

int	execute_simple_command(t_simple_com *simple, int pipe_in, int pipe_out,
		int fd_to_close)
{
	t_builtin_func	*builtin;
	int				result;
	int				already_forked;

	result = EXECUTION_SUCCESS;
	already_forked = 0;
	if (pipe_in != NO_PIPE || pipe_out != NO_PIPE)
	{
		if (make_child() == 0)
		{
			already_forked = 1;
			if (fd_to_close)
			{
				close(fd_to_close);
				fd_to_close = 0;
			}
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
	builtin = find_builtin(simple->words->word);
	if (builtin)
	{
		if (already_forked)
			execute_subshell_builtin(builtin, simple->words, simple->redirects);
		else
			result = (execute_builtin(builtin, simple->words,
						simple->redirects));
	}
	else
		result = execute_disk_command(simple, pipe_in, pipe_out, fd_to_close,
				already_forked);
	return (result);
}
