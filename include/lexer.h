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

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "Error: malloc error.\n"
# endif

# include "libft.h"

typedef struct s_token
{
	char	type;
	char	*content;
}		t_token;

t_list	*separate_words(char *job);
void	remove_empty_words(t_list **words);
t_list	*tokenizer(t_list **words);
void	clear_words(t_list **words);

#endif
