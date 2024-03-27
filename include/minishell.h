/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/27 11:40:54 by sguzman          ###   ########.fr       */
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

/* ************************************************************************** */
/*       Instructions describing what kind of thing to do for a redirection.  */
/* ************************************************************************** */
typedef enum e_instruction
{
	r_output_direction,
	r_input_direction,
	r_appending_to,
	r_reading_until
}							t_instruction;

/* ************************************************************************** */
/*                              Command Types                                 */
/* ************************************************************************** */
typedef enum e_command_type
{
	cm_simple,
	cm_connection,
	cm_subshell
}							t_command_type;

/* ************************************************************************** */
/*                          A linked list of words.                           */
/* ************************************************************************** */
typedef struct s_word_list
{
	char					*word;
	struct s_word_list		*next;
}							t_word_list;

/* ************************************************************************** */
/*                          Structure describing a redirection.               */
/* ************************************************************************** */
typedef struct s_redirect
{
	char					*redirector;
	int						rflags;
	int						flags;
	t_instruction			instruction;
	char					*redirectee;
	char					*here_doc_eof;
	struct s_redirect		*next;
}							t_redirect;

/* ************************************************************************** */
/*                        Definition of the Command  Structure                */
/* ************************************************************************** */
typedef struct s_command
{
	t_command_type			type;
	union
	{
		struct s_connection	*connection;
		struct s_simple_com	*simple;
	} u_value;
}							t_command;

/* ************************************************************************** */
/*             Structure used to represent the CONNECTION type.               */
/* ************************************************************************** */
typedef struct s_connection
{
	t_command				*first;
	t_command				*second;
	int						connector;
}							t_connection;

/* ************************************************************************** */
/*         The "simple" command.  Just a collection of words and redirects.   */
/* ************************************************************************** */
typedef struct s_simple_com
{
	int						flags;
	int						line;
	t_word_list				*words;
	t_redirect				*redirects;
}							t_simple_com;
/* ************************************************************************** */
/*                               Readline functions                           */
/* ************************************************************************** */
char						*readline(const char *prompt);

/* ************************************************************************** */
/*                             POSIX shell specification                      */
/* ************************************************************************** */
void						exit_shell(int s);

/* ************************************************************************** */
/*                            reading and evaluating commands                 */
/* ************************************************************************** */
int							reader_loop(void);
int							read_command(void);

/* ************************************************************************** */
/*                         Miscellaneous functions from parsing               */
/* ************************************************************************** */
int							parse(char *token);

/* ************************************************************************** */
/*                                   Execute CMD                              */
/* ************************************************************************** */
int							execute_command(t_command *command);

#endif
