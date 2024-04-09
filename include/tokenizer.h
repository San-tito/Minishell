/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tokens_id.h"

typedef	struct s_token_range
{
	char	*first;
	size_t	len;
}		t_token_range;

# ifndef AND_ERROR
#  define AND_ERROR "Error: single AND found.\n"
# endif

char	handle_str(t_token_range *token_range, t_list **tokens, t_list **words);
char	handle_parentheses(t_token_range *token_range, t_list **tokens, t_list **words, char token);
char	handle_and(t_token_range *token_range, t_list **tokens, t_list **words, char extended);
char	handle_or(t_token_range *token_range, t_list **tokens, t_list **words, char extended);
char	handle_in(t_token_range *token_range, t_list **tokens, t_list **words, char extended);
char	handle_out(t_token_range *token_range, t_list **tokens, t_list **words, char extended);

void	handle_error(t_list **words, t_list **tokens, char *error_msg);

#endif
