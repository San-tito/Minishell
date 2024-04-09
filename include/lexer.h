/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "token.h"

t_list	*separate_words(char *job);
void	remove_empty_words(t_list **words);
t_list	*tokenizer(t_list **words);
void	remove_quotes(t_list **tokens);
void	check_tokens(t_list **tokens);

//error management
void	handle_word_error(t_list **words, char *error_msg);
void	handle_token_error(t_list **tokens, char *error_msg);
void	handle_error(t_list **words, t_list **tokens, char *error_msg);


//only used on testing I think
void	clear_words(t_list **words);
void	clear_tokens(t_list **tokens);

#endif
