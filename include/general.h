/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:49:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/07 23:34:37 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# define FS_EXISTS 0x1
# define FS_EXECABLE 0x2
# define FS_DIRECTORY 0x10
# define FS_READABLE 0x40

typedef int					t_builtin_func(t_word_list *);

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
/*                              functions for list                            */
/* ************************************************************************** */
int							list_length(t_generic_list *list);
t_generic_list				*list_append(t_generic_list *head,
								t_generic_list *tail);
void						list_remove(t_generic_list **list);
char						**wlist_to_carray(t_word_list *list);

/* ************************************************************************** */
/*                            reading and evaluating commands                 */
/* ************************************************************************** */
int							reader_loop(void);
char						*read_command(void);

/* ************************************************************************** */
/*                            Builtin functions                               */
/* ************************************************************************** */
t_builtin_func				*find_builtin(char *name);

/* ************************************************************************** */
/*                             POSIX shell specification                      */
/* ************************************************************************** */
void						exit_shell(int s);

/* ************************************************************************** */
/*                         Miscellaneous functions from parsing               */
/* ************************************************************************** */
t_command					*parse_command(char *token);

/* ************************************************************************** */
/*                           Functions from print_cmd.c                       */
/* ************************************************************************** */
void						print_command(t_command *command);
void						print_simple_command(t_simple_com *simple_command);

#endif
