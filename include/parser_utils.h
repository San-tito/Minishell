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

t_list		*lexer(char *job);
void		handle_heredocs(t_list **tokens);
t_command	*convert_tokens(t_list **tokens);

t_command	*manage_subshell(t_list **tokens);
t_command	*create_simple_command(t_list **tokens);

#endif
