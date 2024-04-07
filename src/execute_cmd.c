/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 18:33:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_execve(const char *command, char **args, char **env)
{
	int	errnum;
	int	last_command_exit_value;

	last_command_exit_value = 0;
	execve(command, args, env);
	errnum = errno;
	if (errnum != ENOEXEC)
	{
		last_command_exit_value = EX_NOEXEC;
		if (errnum == ENOENT)
			last_command_exit_value = EX_NOTFOUND;
		if (file_status(command) & FS_DIRECTORY)
			internal_error("%s: %s", command, strerror(EISDIR));
		else
			internal_error("%s: %s", command, strerror(errnum));
	}
	return (last_command_exit_value);
}

static int	execute_disk_command(t_word_list *words, t_redirect *redirects,
		pid_t *last_made_pid)
{
	pid_t		pid;
	char		**args;
	const char	*pathname = words->word;
	const char	*command = search_for_command(pathname);

	pid = make_child(last_made_pid);
	if (pid == 0)
	{
		if (command == 0)
		{
			internal_error("%s: command not found", pathname);
			exit(EX_NOTFOUND);
		}
		if (redirects && (do_redirections(redirects) != 0))
			exit(EXECUTION_FAILURE);
		args = strvec_from_word_list(words);
		exit(shell_execve(command, args, environ));
	}
	sh_free((void *)command);
	return (EXECUTION_SUCCESS);
}

int	execute_command(t_command *command)
{
	pid_t		last_made_pid;
	int			result;
	t_word_list	*words;
	t_redirect	*redirects;

	words = ((t_simple_com *)command->value)->words;
	redirects = ((t_simple_com *)command->value)->redirects;
	result = execute_disk_command(words, redirects, &last_made_pid);
	result = wait_for(last_made_pid);
	printf("exit_value -> (%i)\n", result);
	return (result);
}
