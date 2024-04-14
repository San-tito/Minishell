/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:22:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/14 14:50:44 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Replace the '➜' symbol in the prompt with '❯' */
#define SYMBOL "❯ "
#define CYAN "\001\033[1;36m\002"
#define GREEN "\001\033[1;32m\002"
#define RED "\001\033[1;31m\002"
#define YELLOW "\001\033[1;33m\002"
#define RESET "\001\033[0m\002"

char	*get_primary_prompt(void)
{
	static char	prompt[256];
	const char	*home = getenv("HOME");
	const char	*pwd = getenv("PWD");

	if (home && pwd && ft_strncmp(home, pwd, ft_strlen(home)) == 0)
	{
		ft_strlcpy(prompt, "\n" CYAN "~", sizeof(prompt));
		ft_strlcat(prompt, pwd + ft_strlen(home), sizeof(prompt));
	}
	else
	{
		ft_strlcpy(prompt, "\n" CYAN, sizeof(prompt));
		ft_strlcat(prompt, pwd, sizeof(prompt));
	}
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
