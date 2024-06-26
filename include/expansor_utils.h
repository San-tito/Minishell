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
# define EXPANDED 1
# define NOT_EXPANDED 0
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

void	join_and_free(char **str, char **str_to_add);
void	append_env_vars(char **value, char **content_before,
			t_list **environment_vars, t_content_data *content_data);
void	expand_env_var(char **content, t_content_data *content_data,
			t_list **environment_vars);
void	append_last_chars(t_list **environment_vars,
			t_content_data content_data, char expanded);
void	init_data(t_content_data *content_data, char *content, char *expanded);
void	get_matches(char **pattern, t_list **environment_vars);
void	append_content_before(char **content_before, t_list **environment_vars);
void	expand_wildcards(t_list **tokens, t_list **new_tokens);

#endif
