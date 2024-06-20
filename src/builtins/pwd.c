/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:38:29 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/20 23:36:52 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_word_list *list)
{
	char	*directory;

	(void)list;
	directory = getcwd(0, 0);
	if (directory)
	{
		ft_putendl_fd(directory, 1);
		sh_free(directory);
		return (EXECUTION_SUCCESS);
	}
	else
		return (EXECUTION_FAILURE);
}
