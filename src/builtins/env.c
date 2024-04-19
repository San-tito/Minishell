/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:18:39 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:57:15 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	env_builtin(t_word_list *list)
{
	char	**envp;

	(void)list;
	envp = environ;
	while (*envp)
		printf("%s\n", *envp++);
	return (EXECUTION_SUCCESS);
}
