/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:22:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/28 17:30:31 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "input.h"
#include "minishell.h"
#include <stdio.h>

char	*get_primary_prompt(void)
{
	static char	prompt[256];
	const char	*home = getenv("HOME");
	const char	*pwd = getenv("PWD");

	ft_strlcpy(prompt, "\n" CYAN, sizeof(prompt));
	if (home && pwd && ft_strncmp(home, pwd, ft_strlen(home)) == 0)
	{
		ft_strlcat(prompt, "~", sizeof(prompt));
		ft_strlcat(prompt, pwd + ft_strlen(home), sizeof(prompt));
	}
	else if (pwd)
		ft_strlcat(prompt, pwd, sizeof(prompt));
	ft_strlcat(prompt, RESET "\n", sizeof(prompt));
	if (g_last_exit_value == 0)
		ft_strlcat(prompt, GREEN, sizeof(prompt));
	else
		ft_strlcat(prompt, RED, sizeof(prompt));
	ft_strlcat(prompt, SYMBOL RESET, sizeof(prompt));
	return (prompt);
}

char	*get_secondary_prompt(void)
{
	return (YELLOW SYMBOL RESET);
}
