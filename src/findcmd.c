/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:32:10 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 16:38:04 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	absolute_program(const char *string)
{
	return (ft_strchr(string, '/') != NULL);
}

char	*search_for_command(const char *pathname)
{
	char	*command;
	char	*path_list;

	path_index = 0;
	path_list = getenv("PATH");
}
