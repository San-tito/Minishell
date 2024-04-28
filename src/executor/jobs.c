/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:21:31 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/28 15:44:05 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "minishell.h"
#include <errno.h>

pid_t	last_made_pid = NO_PID;
int		already_making_children = 0;

pid_t	make_child(void)
{
	pid_t	pid;

	already_making_children = 1;
	pid = fork();
	if (pid < 0)
	{
		/* Handle Error Exit Status EX_NOEXEC */
		exit(EX_NOEXEC);
	}
	last_made_pid = pid;
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

	while (errno != ECHILD)
	{
		got_pid = waitpid(-1, &status, WUNTRACED | WCONTINUED);
		if (got_pid == pid)
			return_val = process_exit_status(status);
	}
	return (return_val);
}
