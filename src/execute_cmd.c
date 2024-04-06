/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 22:48:21 by sguzman          ###   ########.fr       */
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

static int	execute_disk_command(t_word_list *words)
{
	char		**args;
	const char	*pathname = words->word;
	const char	*command = search_for_command(pathname);

	if (command == 0)
	{
		internal_error("%s: command not found", pathname);
		exit(EX_NOTFOUND);
	}
	args = strvec_from_word_list(words);
	exit(shell_execve(command, args, environ));
}

int	execute_command(t_command *command)
{
	int			result;
	t_word_list	*words;

	(void)command;
	words = sh_malloc(sizeof(t_word_list *));
	words->word = "marcel";
	words->next = NULL;
	result = execute_disk_command(words);
	return (result);
}
