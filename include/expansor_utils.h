/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:25:37 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:26:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_UTILS_H
# define EXPANSOR_UTILS_H

# include "ft_printf.h"
# include "token.h"
# include "parser_error.h"
# include <dirent.h>
# include <sys/types.h>
# include "sh_malloc.h"

# define CORRECT 1
# define ERROR -1
# define MATCH 1
# define NO_MATCH 0

typedef struct s_content_data
{
	char	*start;
	int		last_space;
	int		len;
	char	single_q;
	char	double_q;
}		t_content_data;

char			append_content(char **new_content, t_content_data content_data);
char			expand_value(char **new_content, char **content);
t_content_data	initialize_content(char *token_content, char **content,
	char **new_content);
char			finalize_content(t_token *token, char **new_content,
	t_content_data content_data);
char	join_and_free(char **str, char **str_to_add);
char			expand_wildcards(t_list **tokens);

#endif
