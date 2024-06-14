/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:21:31 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/14 15:15:57 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "minishell.h"
#include "sig.h"
#include <errno.h>
#include <stdio.h>

void	print_status(int status)
{
	if (WIFSIGNALED(status))
		if (WTERMSIG(status) == SIGQUIT)
			fprintf(stderr, "%s ", "Quit");
	if ((WIFSTOPPED(status) == 0) && (WIFCONTINUED(status) == 0)
		&& WCOREDUMP(status))
		fprintf(stderr, "%s", "(core dumped) ");
	if (WIFSIGNALED(status))
		fprintf(stderr, "\n");
}

pid_t	make_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EX_NOEXEC);
	return (pid);
}

int	process_exit_status(int status)
{
	print_status(status);
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
