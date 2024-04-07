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

typedef	struct s_token_range
{
	char	*first;
	size_t	len;
}		t_token_range;

# ifndef STR_TOKEN
#  define STR_TOKEN 0
# endif

# ifndef OPEN_PARENTHESIS_TOKEN
#  define OPEN_PARENTHESIS_TOKEN 1
# endif

# ifndef CLOSE_PARENTHESIS_TOKEN
#  define CLOSE_PARENTHESIS_TOKEN 2
# endif

#endif
