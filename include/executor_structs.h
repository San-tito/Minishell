/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_structs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_STRUCTS_H
# define EXECUTOR_STRUCTS_H

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

#endif
