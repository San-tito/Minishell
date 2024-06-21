/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:18:39 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 18:21:49 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_word_list *list)
{
	char	**envp;

	(void)list;
	envp = environ;
	while (*envp && ft_strchr(*envp, '='))
		ft_putendl_fd(*envp++, 1);
	return (EXECUTION_SUCCESS);
}
