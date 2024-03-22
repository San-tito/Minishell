/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/20 16:19:49 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

char	*readline(const char *prompt);

/* ************************************************************************** */
/*                             POSIX shell specification                      */
/* ************************************************************************** */
void	exit_shell(int s);

/* ************************************************************************** */
/*                            reading and evaluating commands                 */
/* ************************************************************************** */
int		reader_loop(void);
int		read_command(void);

#endif
