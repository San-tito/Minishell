/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:21:31 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/15 22:31:06 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "minishell.h"
#include "sig.h"
#include <errno.h>
#include <stdio.h>

void	print_status(int status)
{
	int	term_signal;

	if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		if (term_signal == SIGQUIT)
			fprintf(stderr, "Quit ");
		else if (term_signal == SIGKILL)
			fprintf(stderr, "Killed ");
		else if (term_signal == SIGTERM)
			fprintf(stderr, "Terminated ");
		else if (term_signal == SIGSEGV)
			fprintf(stderr, "Segmentation fault ");
		if (WCOREDUMP(status))
			fprintf(stderr, "(core dumped) ");
		fprintf(stderr, "\n");
	}
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
