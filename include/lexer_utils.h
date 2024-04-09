/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

# include "libft.h"
# include "token.h"

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "Error: not enough space (malloc function error).\n"
# endif

# ifndef SINGLE_Q_ERROR
#  define SINGLE_Q_ERROR "Error: single quotes opened but not clossed.\n"
# endif

# ifndef DOUBLE_Q_ERROR
#  define DOUBLE_Q_ERROR "Error: double quotes opened but not clossed.\n"
# endif

# ifndef AND_ERROR
#  define AND_ERROR "Error: '&' token cannot be single.\n"
# endif

# ifndef CLOSED_PARENTESIS_ERROR
#  define CLOSED_PARENTESIS_ERROR "Error: closing parenthesis without opening one.\n"
# endif

# ifndef PARENTESIS_NOT_CLOSED_ERROR
#  define PARENTESIS_NOT_CLOSED_ERROR "Error: more parentesis opened than closed.\n"
# endif

# ifndef AND_BOUNDARY_ERROR
#  define AND_BOUNDARY_ERROR "Error: syntax error near unexpected token '&&'.\n"
# endif

# ifndef PIPE_BOUNDARY_ERROR
#  define PIPE_BOUNDARY_ERROR "Error: syntax error near unexpected token '|'.\n"
# endif

# ifndef OR_BOUNDARY_ERROR
#  define OR_BOUNDARY_ERROR "Error: syntax error near unexpected token '||'.\n"
# endif

# ifndef HEREDOC_BOUNDARY_ERROR
#  define HEREDOC_BOUNDARY_ERROR "Error: syntax error near unexpected token '<<'.\n"
# endif

# ifndef APPEND_BOUNDARY_ERROR
#  define APPEND_BOUNDARY_ERROR "Error: syntax error near unexpected token '>>'.\n"
# endif

# ifndef NEWLINE_BOUNDARY_ERROR
#  define NEWLINE_BOUNDARY_ERROR "Error: syntax error near unexpected token 'newline'.\n"
# endif

//error management
void	handle_word_error(t_list **words, char *error_msg);
void	handle_token_error(t_list **tokens, char *error_msg);
void	handle_error(t_list **words, t_list **tokens, char *error_msg);

//only used on testing I think
void	del_word(void *content);
void	clear_words(t_list **words);
void	del_token(void *content);
void	clear_tokens(t_list **tokens);

#endif
