/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:21:31 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/23 14:56:21 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "minishell.h"
#include <errno.h>

pid_t	make_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		/* Handle Error Exit Status EX_NOEXEC */
		exit(EX_NOEXEC);
	}
	/* Clean process that has the same pid */
	/* add process */
	return (pid);
}

int	process_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

int	waitchld(pid_t pid)
{
	pid_t	got_pid;
	int		status;
	int		return_val;

	got_pid = 1;
	while (got_pid > (pid_t)0)
	{
		got_pid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
		if (got_pid < 0 && errno == ECHILD)
			status = 0;
	}
	return_val = process_exit_status(status);
	return (return_val);
}
