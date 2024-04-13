/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:38:29 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/13 15:41:39 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_word_list *list)
{
	char	*directory;

	(void)list;
	directory = getcwd(0, 0);
	if (directory)
	{
		printf("%s\n", directory);
		return (EXECUTION_SUCCESS);
	}
	else
		return (EXECUTION_FAILURE);
}
