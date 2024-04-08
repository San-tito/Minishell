/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_words.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/03/10 16:29:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_WORDS_H
# define SEPARATE_WORDS_H

# include "./libft.h"

# ifndef SINGLE_Q_ERROR
#  define SINGLE_Q_ERROR "Error: single quotes opened but not clossed.\n"
# endif

# ifndef DOUBLE_Q_ERROR
#  define DOUBLE_Q_ERROR "Error: double quotes opened but not clossed.\n"
# endif

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "Error: malloc error.\n"
# endif

typedef	struct s_word_data
{
	char	*first;
	size_t	len;
	char	single_q;
	char	double_q;
}		t_word_data;

void	handle_error_word(t_list **words, char *error_msg);

#endif
