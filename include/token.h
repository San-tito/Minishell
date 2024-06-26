/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2024/04/23 14:51:49 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	char	type;
	char	*content;
}		t_token;

# ifndef STR_TOKEN
#  define STR_TOKEN 0
# endif

# ifndef OPEN_PAR_TOKEN
#  define OPEN_PAR_TOKEN 1
# endif

# ifndef CLOSE_PAR_TOKEN
#  define CLOSE_PAR_TOKEN 2
# endif

# ifndef AND_TOKEN
#  define AND_TOKEN 3
# endif

# ifndef PIPE_TOKEN
#  define PIPE_TOKEN 124
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

#endif
