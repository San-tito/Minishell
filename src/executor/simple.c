/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:50:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/25 19:50:55 by santito          ###   ########.fr       */
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
		return (EXECUTION_FAILURE);
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

static int	execute_disk_command(t_word_list *words, t_redirect *redirects)
{
	char		**args;
	const char	*pathname = words->word;
	const char	*command = search_for_command(pathname);

	if (command)
		update_env("_=", command);
	if (redirects && (do_redirections(redirects) != 0))
		exit(EXECUTION_FAILURE);
	if (command == 0)
	{
		internal_error("%s: command not found", pathname);
		exit(EX_NOTFOUND);
	}
	args = wlist_to_carray(words);
	exit(shell_execve(command, args, environ));
}

int	execute_simple_command(t_simple_com *simple, int pipe_in, int pipe_out,
		int fd_to_close)
{
	t_builtin_func	*builtin;
	int				result;

	result = EXECUTION_SUCCESS;
	builtin = find_builtin(simple->words->word);
	if (builtin && pipe_in == NO_PIPE && pipe_out == NO_PIPE)
		return (execute_builtin(builtin, simple->words, simple->redirects));
	if (make_child() == 0)
	{
		if (fd_to_close)
			close(fd_to_close);
		do_piping(pipe_in, pipe_out);
		if (builtin)
			return (execute_subshell_builtin(builtin, simple->words,
					simple->redirects));
		else
			return (execute_disk_command(simple->words, simple->redirects));
	}
	if (pipe_out != NO_PIPE)
		result = g_last_exit_value;
	close_pipes(pipe_in, pipe_out);
	return (result);
}
