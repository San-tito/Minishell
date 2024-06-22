/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "token.h"
# include "parser_error.h"
# include "ft_printf.h"

typedef struct s_token_range
{
	char	*first;
	size_t	len;
	char	error;
}		t_token_range;

char	add_token(char token_type, char *data, t_list **tokens,
			t_list **words);
void	create_str_token(t_token_range *token_range, t_list **tokens,
			t_list **words);
char	handle_str(t_token_range *token_range, t_list **tokens,
			t_list **words);
char	handle_parentheses(t_token_range *token_range, t_list **tokens,
			t_list **words, char token);
char	handle_and(t_token_range *token_range, t_list **tokens,
			t_list **words, char extended);
char	handle_or(t_token_range *token_range, t_list **tokens,
			t_list **words, char extended);
char	handle_in(t_token_range *token_range, t_list **tokens,
			t_list **words, char extended);
char	handle_out(t_token_range *token_range, t_list **tokens,
			t_list **words, char extended);

#endif
