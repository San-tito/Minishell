/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:23:18 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 17:23:48 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_builtin_func	*find_builtin(char *name)
{
	const t_builtin	builtins[] = {
	{"cd", cd_builtin},
	{"echo", echo_builtin},
	{"env", env_builtin},
	{"export", export_builtin},
	{"pwd", pwd_builtin},
	{"unset", unset_builtin},
	{"exit", exit_builtin}
	};
	const int		num_builtins = sizeof(builtins) / sizeof(*builtins);
	int				i;

	i = 0;
	while (i < num_builtins)
	{
		if (ft_strncmp(name, builtins[i].name, ft_strlen(builtins[i].name)) == 0
			&& name[ft_strlen(builtins[i].name)] == '\0')
			return (builtins[i].function);
		i++;
	}
	return (NULL);
}
