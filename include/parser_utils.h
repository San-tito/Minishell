/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "libft.h"
# include "executor_structs.h"
# include "token.h"
# include <fcntl.h>
# include "malloc_func.h"

t_command	*create_simple_command(t_list **tokens);
t_command	*manage_subshell(t_list **tokens);
t_command	*make_command(t_command_type type, void *pointer);
t_command	*make_simple_command(t_word_list *words, t_redirect *redirects);
t_word_list	*make_word_list(char *word, t_word_list *head);
t_redirect	*make_redirection(char *filename, t_instruction instruction, t_redirect *head);
//void		make_here_document(t_redirect *temp);

void	clear_command(t_command **command);

#endif
