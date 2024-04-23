/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:12:07 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/23 14:54:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_CMD_H
# define EXECUTE_CMD_H

# include "command.h"

/* ************************************************************************** */
/*                   Functions declared in execute_cmd.c                      */
/* ************************************************************************** */
int			execute_command(t_command *command, int pipe_in, int pipe_out,
				int fd_to_close);
int			shell_execve(const char *command, char **args, char **env);
int			do_redirections(t_redirect *list);

extern int	g_last_exit_value;

#endif
