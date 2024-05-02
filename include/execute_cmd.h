/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:12:07 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/27 13:48:14 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMD_H
# define EXECUTE_CMD_H

# include "command.h"
# include <sys/types.h>

/* ************************************************************************** */
/*                   Functions declared in execute_cmd.c                      */
/* ************************************************************************** */
int			execute_command(t_command *command, int pipe_in, int pipe_out,
				int fd_to_close);
int			execute_simple_command(t_simple_com *simple, int pipeline[2],
				pid_t *last_made_pid, int fd_to_close);
int			execute_connection(t_command *command, int pipe_in, int pipe_out);
void		close_pipes(int in, int out);
void		do_piping(int pipe_in, int pipe_out);
int			do_redirections(t_redirect *list);

extern int	g_last_exit_value;

#endif
