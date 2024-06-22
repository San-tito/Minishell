/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 17:33:32 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bind_variable(char *name, char *value, int attributes)
{
	t_varlist	*vlist;
	t_variable	*temp;

	temp = sh_malloc(sizeof(t_variable));
	temp->name = name;
	temp->value = value;
	temp->attributes = attributes;
	vlist = varlist();
	vlist_add(vlist, temp);
}

void	initialize_shell_variables(char **env)
{
	char	*string;
	char	*name;
	int		index;

	index = 0;
	while (env[index])
		index++;
	index = -1;
	while (env[++index])
	{
		name = sh_strdup(env[index]);
		string = ft_strchr(name, '=');
		if (string == 0)
			continue ;
		name[string++ - name] = '\0';
		if (legal_identifier(name))
			bind_variable(name, string, (ATT_EXPORT));
	}
}

void	initialize_shell_level(void)
{
	char	*old_shlvl;
	ssize_t	old_level;
	int		shell_level;
	char	*new_level;

	old_shlvl = find_env("SHLVL");
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
