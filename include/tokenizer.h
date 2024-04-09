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

# ifndef AND_TOKEN
#  define AND_TOKEN 3
# endif

# ifndef PIPE_TOKEN
#  define PIPE_TOKEN 4
# endif

# ifndef OR_TOKEN
#  define OR_TOKEN 5
# endif

# ifndef INPUT_TOKEN
#  define INPUT_TOKEN 6
# endif

# ifndef HEREDOC_TOKEN
#  define HEREDOC_TOKEN 7
# endif

# ifndef OUTPUT_TOKEN
#  define OUTPUT_TOKEN 8
# endif

# ifndef APPEND_TOKEN
#  define APPEND_TOKEN 9
# endif

# ifndef AND_ERROR
#  define AND_ERROR "Error: single AND found.\n"
# endif

char	is_boundary(char **word, t_token_range *token_range, t_list **tokens, t_list **words);
void	handle_error(t_list **words, t_list **tokens, char *error_msg);

#endif
