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

# include "parser_error.h"
# include "token.h"
# include "sh_malloc.h"

// Struct used inside separate_words
typedef	struct s_word_data
{
	char	*first;
	size_t	len;
	char	single_q;
	char	double_q;
}		t_word_data;

// Struct used inside handle_quotes
typedef struct s_handle_quotes
{
	char	single_quotes;
	char	double_quotes;
	int		num;
}		t_handle_quotes;

// Struct used in check tokens.
typedef struct s_check_par
{
	int		parentesis_used;
	t_list	*lst;
}		t_check_par;

# ifndef MAX_HEREDOC
#  define MAX_HEREDOC 16
# endif

# ifndef MAX_TEXT_ERROR
#  define MAX_TEXT_ERROR 49
# endif

# ifndef ERROR
#  define ERROR 0
# endif

# ifndef CORRECT
#  define CORRECT 1
# endif

//only used on testing I think
void	del_word(void *content);
void	clear_word_list(t_list **words);
void	del_token(void *content);
void	clear_tokens(t_list **tokens);

// Functions called inside lexer.
t_list	*separate_words(char *job);
t_list	*tokenizer(t_list **words);
char	expansor(t_list **tokens);
char	remove_quotes(t_list **tokens);
char	check_tokens(t_list **tokens);

char	check_parentheses(t_list **tokens);

//could be static inside lexer but is used in testing
void	remove_empty_words(t_list **words);

#endif
