/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:21:55 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/21 10:31:13 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_CMD_H
# define MAKE_CMD_H

# include <fcntl.h>

/* ************************************************************************** */
/*                     Declarations of functions found in make_cmd.c          */
/* ************************************************************************** */

t_command	*make_command(t_command_type type, void *pointer);
t_command	*make_simple_command(t_word_list *words, t_redirect *redirects);
t_command	*make_connect(t_command *com1, t_command *com2, int connector);
t_word_list	*make_word_list(char *word, t_word_list *next);
t_redirect	*make_redirection(char *filename, t_instruction instruction,
				t_redirect *head);
void		make_here_document(t_redirect *temp);

#endif
