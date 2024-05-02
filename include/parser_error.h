/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERROR_H
# define PARSER_ERROR_H

# include "ft_printf.h"

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "Error: not enough space (malloc function error)."
# endif

# ifndef SINGLE_Q_ERROR
#  define SINGLE_Q_ERROR "Error: single quotes opened but not clossed."
# endif

# ifndef DOUBLE_Q_ERROR
#  define DOUBLE_Q_ERROR "Error: double quotes opened but not clossed."
# endif

# ifndef AND_ERROR
#  define AND_ERROR "Error: '&' token cannot be single."
# endif

# ifndef CLOSED_PARENTESIS_ERROR
#  define CLOSED_PARENTESIS_ERROR "Error: closing parenthesis without opening one."
# endif

# ifndef PARENTESIS_NOT_CLOSED_ERROR
#  define PARENTESIS_NOT_CLOSED_ERROR "Error: more parentesis opened than closed."
# endif

# ifndef OPEN_PARENTHESIS_BOUNDARY_ERROR
#  define OPEN_PARENTHESIS_BOUNDARY_ERROR "Error: syntax error near unexpected token '('."
# endif

# ifndef CLOSED_PARENTHESIS_BOUNDARY_ERROR
#  define CLOSED_PARENTHESIS_BOUNDARY_ERROR "Error: syntax error near unexpected token ')'."
# endif

# ifndef AND_BOUNDARY_ERROR
#  define AND_BOUNDARY_ERROR "'&&'."
# endif

# ifndef PIPE_BOUNDARY_ERROR
#  define PIPE_BOUNDARY_ERROR "'|'."
# endif

# ifndef OR_BOUNDARY_ERROR
#  define OR_BOUNDARY_ERROR "'||'."
# endif

# ifndef HEREDOC_BOUNDARY_ERROR
#  define HEREDOC_BOUNDARY_ERROR "'<<'."
# endif

# ifndef APPEND_BOUNDARY_ERROR
#  define APPEND_BOUNDARY_ERROR "'>>'."
# endif

# ifndef NEWLINE_BOUNDARY_ERROR
#  define NEWLINE_BOUNDARY_ERROR "'newline'."
# endif

# ifndef MAX_HEREDOC_ERROR
#  define MAX_HEREDOC_ERROR "Error: maximum here-document count exeeded."
# endif

void	del_word(void *content);
void	clear_word_list(t_list **words);
void	del_token(void *content);
void	clear_tokens(t_list **tokens);
char	handle_word_error(t_list **words, char *error_msg);
char	handle_token_error(t_list **tokens, char *error_msg);
char	handle_error(t_list **words, t_list **tokens, char *error_msg);
char	handle_checker_error(t_list **tokens, char *error_msg);

#endif
