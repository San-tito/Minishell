/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:09:36 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 13:23:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

DIR	*sh_opendir(const char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir == NULL)
		fatal_error("Could not open dir %s", str);
	return (dir);
}

char	**sh_split(char *str, char value)
{
	char	**mat;

	mat = ft_split(str, value);
	if (mat == NULL)
		fatal_error("Not enough memory to split string [%s] by value [%c]",
			str, value);
	return (mat);
}
