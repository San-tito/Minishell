/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:21:31 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/21 16:46:11 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "minishell.h"
#include <errno.h>

pid_t				last_made_pid = NO_PID;
int					already_making_children = 0;
t_process			*pipeline = NULL;

void	add_process(pid_t pid)
{
	t_process	*t;

	t = sh_malloc(sizeof(t_process));
	t->pid = pid;
	t->status = 0;
	t->running = 1;
	t->next = NULL;
	list_append((t_generic_list *)pipeline, (t_generic_list *)t);
}

t_process	*find_child(pid_t pid)
{
	t_process	*p;

	p = pipeline;
	while (p)
	{
		if (p->pid == pid)
			return (p);
		p = p->next;
	}
	return (NULL);
}

pid_t	make_child(void)
{
	pid_t	pid;

	already_making_children = 1;
	pid = fork();
	if (pid < 0)
	{
		already_making_children = 0;
		/* Cleanup the pipeline */
		if (pipeline)
			pipeline = NULL;
		/* Handle Error Exit Status EX_NOEXEC */
		exit(EX_NOEXEC);
	}
	/* Clean process that has the same pid */
	/* add process */
	add_process(pid);
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
	pid_t		got_pid;
	int			status;
	int			return_val;

	got_pid = waitpid(-1, &status, WUNTRACED | WCONTINUED);
	while (got_pid != pid)
	{
		if (got_pid < 0 && errno == ECHILD)
		{
			status = 0;
			break ;
		}
		got_pid = waitpid(-1, &status, WUNTRACED | WCONTINUED);
	}
	return_val = process_exit_status(status);
	return (return_val);
}
