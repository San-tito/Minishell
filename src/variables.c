/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/29 11:29:42 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(char *envstr)
{
	int	env_index;

	env_index = 0;
	while (environ[env_index])
		env_index++;
	environ[env_index++] = envstr;
	environ[env_index] = NULL;
}

char	**unset_var(const char *name)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(name, environ[i], ft_strlen(name)) == 0)
		{
			environ[i] = environ[i + 1];
			return (environ);
		}
		i++;
	}
	return (environ);
}

char	**add_or_replace_exported_var(char *assign)
{
	int			i;
	const char	*equal_offset = ft_strchr(assign, '=');

	if (equal_offset == 0)
		return (environ);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(assign, environ[i], equal_offset - assign) == 0)
		{
			environ[i] = assign;
			return (environ);
		}
		i++;
	}
	add_to_env(assign);
	return (environ);
}

void	update_env(const char *env_prefix, const char *value)
{
	char	*evar;

	evar = ft_strjoin(env_prefix, value);
	environ = add_or_replace_exported_var(evar);
}

void	initialize_shell_level(void)
{
	char	*old_shlvl;
	size_t	old_level;
	int		shell_level;
	char	*new_level;

	old_level = 0;
	shell_level = 0;
	old_shlvl = getenv("SHLVL");
	if (old_shlvl)
		old_level = ft_atoi(old_shlvl);
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
	update_env("SHLVL=", new_level);
}
