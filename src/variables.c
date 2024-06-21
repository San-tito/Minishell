/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 20:03:14 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell_level(void)
{
	char	*old_shlvl;
	ssize_t	old_level;
	int		shell_level;
	char	*new_level;

	old_shlvl = getenv("SHLVL");
	if (old_shlvl == 0 || *old_shlvl == '\0' || legal_number(old_shlvl,
			&old_level) == 0)
		old_level = 0;
	shell_level = old_level + 1;
	if (shell_level < 0)
		shell_level = 0;
	else if (shell_level >= 1000)
	{
		internal_warning("shell level (%d) too high, resetting to 1",
			shell_level);
		shell_level = 1;
	}
	new_level = ft_itoa(shell_level);
	update_env("SHLVL", new_level);
	sh_free(new_level);
}

void	set_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(0, 0);
	update_env("PWD", current_dir);
	sh_free(current_dir);
}

char	*find_env(const char *name, int len, int *offset)
{
	char	**p;
	char	*cp;
	char	*eq;

	if (name == NULL || environ == NULL)
		return (NULL);
	p = environ + *offset;
	while (*p)
	{
		cp = *p;
		eq = ft_strchr(cp, '=');
		if (eq == 0)
			continue ;
		if (ft_strncmp(cp, name, len) == 0 && (int)(eq - cp) == len)
		{
			*offset = p - environ;
			return (eq + 1);
		}
		++p;
	}
	return (0);
}
