/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/04/10 17:58:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define NO_PID -1
# define NO_PIPE -1

# define EXECUTION_FAILURE 1
# define EXECUTION_SUCCESS 0

# define EX_NOEXEC 126
# define EX_NOTFOUND 127

# define FD_BITMAP_SIZE 32
# define HEREDOC_MAX 16

# define FS_EXISTS 0x1
# define FS_EXECABLE 0x2
# define FS_DIRECTORY 0x10
# define FS_READABLE 0x40

# define CYAN "\001\033[1;36m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\001\033[1;31m\002"
# define RESET "\001\033[0m\002"

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
	struct s_word_list		*next;
	char					*word;
}							t_word_list;

/* ************************************************************************** */
/*                          Structure describing a redirection.               */
/* ************************************************************************** */
typedef struct s_redirect
{
	struct s_redirect		*next;
	int						dest;
	char					*filename;
	int						flags;
	t_instruction			instruction;
	char					*here_doc_eof;
}							t_redirect;

/* ************************************************************************** */
/*                        Definition of the Command  Structure                */
/* ************************************************************************** */
typedef struct s_command
{
	t_command_type			type;
	void					*value;
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
	t_word_list				*words;
	t_redirect				*redirects;
}							t_simple_com;

/* ************************************************************************** */
/* 	All structs which contain a `next' field should have that field       */
/*   	as the first field in the struct.  This means that functions          */
/*   	can be written to handle the general case for linked lists.           */
/* ************************************************************************** */
typedef struct s_generic_list
{
	struct s_generic_list	*next;
}							t_generic_list;

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
char						*read_command(void);

/* ************************************************************************** */
/*                         Miscellaneous functions from parsing               */
/* ************************************************************************** */
t_command					*parse_command(char *token);

/* ************************************************************************** */
/*                                   Execute CMD                              */
/* ************************************************************************** */
int							execute_command(t_command *command);

/* ************************************************************************** */
/*                                   Find CMD                                 */
/* ************************************************************************** */
char						*search_for_command(const char *pathname);
int							file_status(const char *name);

/* ************************************************************************** */
/*                                   Make CMD                                 */
/* ************************************************************************** */
t_command					*make_command(t_command_type type, void *pointer);
t_command					*make_simple_command(t_word_list *words,
								t_redirect *redirects);
t_word_list					*make_word_list(char *word, t_word_list *next);
t_redirect					*make_redirection(char *filename,
								t_instruction instruction, t_redirect *head);

/* ************************************************************************** */
/*                                   Clear CMD                                */
/* ************************************************************************** */
void						clear_command(t_command *command);
void						clear_words(t_word_list *list);
void						clear_redirects(t_redirect *list);

/* ************************************************************************** */
/*                            Report an internal error.                       */
/* ************************************************************************** */
void						internal_error(const char *format, ...);

/* ************************************************************************** */
/*                              functions for list                            */
/* ************************************************************************** */
int							list_length(t_generic_list *list);
t_generic_list				*list_append(t_generic_list *head,
								t_generic_list *tail);
char						**strvec_from_word_list(t_word_list *list);

/* ************************************************************************** */
/*                                   Jobs                                     */
/* ************************************************************************** */
pid_t						make_child(void);
int							wait_for(pid_t pid);

/* ************************************************************************** */
/*                                   Do Redirections                          */
/* ************************************************************************** */
int							do_redirections(t_redirect *list);

/* ************************************************************************** */
/*                            Allocation functions                            */
/* ************************************************************************** */
void						*sh_malloc(size_t bytes);
void						sh_free(void *string);
void						sh_doublefree(void **array);

extern char					**environ;
extern int					g_last_exit_value;

#endif
