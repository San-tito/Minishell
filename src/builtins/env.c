/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:18:39 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/12 13:40:06 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_word_list *list)
{
	char	**envp;

	(void)list;
	envp = environ;
	while (*envp)
		ft_putendl_fd(*envp++, 1);
	return (EXECUTION_SUCCESS);
}
