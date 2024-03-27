/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/27 20:00:54 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static int			execute_simple_command(t_simple_com *simple_command,
						int pipe_in, int pipe_out, int async,
						struct fd_bitmap *fds_to_close);
static int			execute_connection(t_command *command, int asynchronous,
						int pipe_in, int pipe_out,
						struct fd_bitmap *fds_to_close);

static void			do_piping(int pipe_in, int pipe_out);
static void			close_pipes(int in, int out);

struct fd_bitmap	*new_fd_bitmap(int size)
{
	struct fd_bitmap	*ret;

	ret = ft_malloc(sizeof(struct fd_bitmap));
	ret->size = size;
	if (size)
	{
		ret->bitmap = ft_malloc(size);
		memset(ret->bitmap, '\0', size);
	}
	else
		ret->bitmap = NULL;
	return (ret);
}

int	execute_command(t_command *command)
{
	struct fd_bitmap	*bitmap;
	int					result;

	bitmap = new_fd_bitmap(FD_BITMAP_SIZE);
	result = execute_command_internal(command, 0, NO_PIPE, NO_PIPE, bitmap);
	return (result);
}

int	execute_command_internal(t_command *command, int asynchronous, int pipe_in,
		int pipe_out, struct fd_bitmap *fds_to_close)
{
	int	exec_result;

	exec_result = EXECUTION_SUCCESS;
	if (command->type == cm_simple)
		exec_result = execute_simple_command((t_simple_com *)command->value,
				pipe_in, pipe_out, asynchronous, fds_to_close);
	else if (command->type == cm_connection)
		exec_result = execute_connection(command, asynchronous, pipe_in,
				pipe_out, fds_to_close);
	return (exec_result);
}

static int	execute_connection(t_command *command, int asynchronous,
		int pipe_in, int pipe_out, struct fd_bitmap *fds_to_close)
{
	(void)command;
	(void)asynchronous;
	(void)pipe_in;
	(void)pipe_out;
	(void)fds_to_close;
	return (0);
}

static int	execute_simple_command(t_simple_com *simple_command, int pipe_in,
		int pipe_out, int async, struct fd_bitmap *fds_to_close)
{
	int	result;

	result = EXECUTION_SUCCESS;
	if (pipe_in != NO_PIPE || pipe_out != NO_PIPE || async)
	{
		if (fork())
		{
			do_piping(pipe_in, pipe_out);
		}
		else
		{
			close_pipes(pipe_in, pipe_out);
			return (result);
		}
	}
	return (result);
}

static void	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != NO_PIPE)
	{
		if (dup2(pipe_in, 0) < 0)
			/* dup_error(pipe_in, 0); */
			if (pipe_in > 0)
				close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		if (dup2(pipe_out, 1) < 0)
			/* dup_error(pipe_out, 1); */
			if (pipe_out == 0 || pipe_out > 1)
				close(pipe_out);
	}
}

static void	close_pipes(int in, int out)
{
	if (in >= 0)
		close(in);
	if (out >= 0)
		close(out);
}
