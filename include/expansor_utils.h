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

# define CORRECT 1
# define ERROR -1

typedef struct s_content_data
{
	char	*start;
	int		len;
	char	single_q;
	char	double_q;
}		t_content_data;

char	append_content(char **new_content, t_content_data content_data);
char	expand_value(char **new_content, char **content);

#endif
