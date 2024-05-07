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

typedef struct s_word
{
	char	*start;
	int		len;
}		t_word;

#endif
