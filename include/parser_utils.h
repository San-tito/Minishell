/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "ft_printf.h"
# include "make_cmd.h"
# include "clear_cmd.h"
# include "token.h"
# include "parser_error.h"
# include "sh_malloc.h"

# ifndef ERROR
#  define ERROR 0
# endif

# ifndef CORRECT
#  define CORRECT 1
# endif

t_list		*lexer(char *job);
void		handle_heredocs(t_list **tokens);
t_command	*parse_tokens(t_list **tokens);

t_command	*create_subshell(t_list **tokens);
t_command	*create_simple_command(t_list **tokens);

#endif
