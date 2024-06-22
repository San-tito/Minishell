/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 18:19:24 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char	*find_env(const char *name)
{
	t_varlist	*vlist;
	int			i;

	i = 0;
	vlist = varlist();
	while (i < vlist->list_len)
	{
		if (ft_strncmp(name, vlist->list[i]->name, ft_strlen(name) + 1) == 0
			&& vlist->list[i]->name[ft_strlen(name)] == '\0')
			return (vlist->list[i]->value);
		i++;
	}
	return (0);
}

int	delete_env(const char *name)
{
	(void)name;
	if (name == 0 || *name == 0 || ft_strchr(name, '='))
		return (errno = EINVAL, -1);
	return (0);
}

int	update_env(const char *name, char *value)
{
	int			i;
	t_varlist	*vlist;

	if (name == 0 || *name == 0 || ft_strchr(name, '='))
		return (errno = EINVAL, -1);
	i = 0;
	vlist = varlist();
	while (i < vlist->list_len)
	{
		if (ft_strncmp(name, vlist->list[i]->name, ft_strlen(name) + 1) == 0
			&& vlist->list[i]->name[ft_strlen(name)] == '\0')
		{
			vlist->list[i]->value = sh_strdup(value);
		}
		i++;
	}
	if (i == vlist->list_len)
		bind_variable(sh_strdup(name), sh_strdup(value), (ATT_EXPORT));
	return (0);
}

int	add_exported(char *name, int append)
{
	if (name == 0 || *name == 0)
		return (errno = EINVAL, -1);
	(void)append;
	return (0);
}
