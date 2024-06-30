/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:50:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/30 14:20:09 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "findcmd.h"
#include "jobs.h"
#include "minishell.h"
#include "sig.h"
#include <errno.h>
#include <string.h>

static int	shell_execve(const char *command, char **args, char **env)
{
	int	errnum;

	*last_exit_value() = 0;
	execve(command, args, env);
	errnum = errno;
	if (errnum != ENOEXEC)
	{
		*last_exit_value() = EX_NOEXEC;
		if (errnum == ENOENT)
			*last_exit_value() = EX_NOTFOUND;
		if (file_status(command) & FS_DIRECTORY)
			internal_error("%s: %s", command, strerror(EISDIR));
		else
			internal_error("%s: %s", command, strerror(errnum));
	}
	sh_doublefree((void **)args);
	sh_doublefree((void **)env);
	return (*last_exit_value());
}

static int	execute_subshell_builtin(t_builtin_func *builtin,
		t_word_list *words, t_redirect *redirects)
{
	int	result;

	if (redirects && (do_redirections(redirects) != 0))
		sh_exit(EXECUTION_FAILURE);
	result = ((*builtin)(words->next));
	sh_exit(result);
	return (result);
}

static int	execute_builtin(t_builtin_func *builtin, t_word_list *words,
		t_redirect *redirects)
{
	int			result;
	const int	in = dup(0);
	const int	out = dup(1);

	if (redirects && (do_redirections(redirects) != 0))
		return (do_piping(in, out), close_pipes(in, out), EXECUTION_FAILURE);
	result = ((*builtin)(words->next));
	do_piping(in, out);
	close_pipes(in, out);
	return (result);
}

static int	execute_disk_command(char *command, t_word_list *words,
		t_redirect *redirects)
{
	char	**args;

	reset_terminating_signals();
	if (redirects && (do_redirections(redirects) != 0))
		sh_exit(EXECUTION_FAILURE);
	if (command == 0)
	{
		internal_error("%s: command not found", words->word);
		sh_exit(EX_NOTFOUND);
	}
	args = wlist_to_carray(words);
	sh_exit(shell_execve(command, args, vlist_to_carray()));
	return (EXECUTION_SUCCESS);
}

int	execute_simple_command(t_simple_com *simple, int pipeline[2],
		pid_t *last_made_pid, int fd_to_close)
{
	t_builtin_func	*builtin;
	char			*command;

	builtin = find_builtin(simple->words->word);
	command = search_for_command(simple->words->word);
	if (builtin && pipeline[0] == NO_PIPE && pipeline[1] == NO_PIPE)
		return (sh_free((void *)command), execute_builtin(builtin,
				simple->words, simple->redirects));
	*last_made_pid = make_child();
	if (*last_made_pid == 0)
	{
		close_fd(fd_to_close);
		do_piping(pipeline[0], pipeline[1]);
		if (builtin)
			return (sh_free((void *)command), execute_subshell_builtin(builtin,
					simple->words, simple->redirects));
		execute_disk_command(command, simple->words, simple->redirects);
	}
	if (command)
		update_env("_", command);
	sh_free((void *)command);
	if (pipeline[1] != NO_PIPE)
		return (close_pipes(pipeline[0], pipeline[1]), *last_exit_value());
	return (close_pipes(pipeline[0], pipeline[1]), EXECUTION_SUCCESS);
}
