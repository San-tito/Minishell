/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:21:31 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/14 15:06:36 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile pid_t	last_made_pid = NO_PID;
int				already_making_children = 0;

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
	return (pid);
}

int	process_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (WEXITSTATUS(status));
}

int	wait_for(pid_t pid)
{
	int	status;
	int	return_val;

	if (waitpid(pid, &status, WUNTRACED | WCONTINUED) != pid)
		/* Handle Error  */
		exit(EXECUTION_FAILURE);
	return_val = process_exit_status(status);
	return (return_val);
}
