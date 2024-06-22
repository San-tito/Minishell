/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 21:51:06 by sguzman          ###   ########.fr       */
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
	t_varlist	*vlist;
	int			i;
	int			j;

	if (name == 0 || *name == 0 || ft_strchr(name, '='))
		return (errno = EINVAL, -1);
	i = 0;
	vlist = varlist();
	while (i < vlist->list_len)
	{
		if (ft_strncmp(name, vlist->list[i]->name, ft_strlen(name) + 1) == 0
			&& vlist->list[i]->name[ft_strlen(name)] == '\0')
		{
			clear_variable(vlist->list[i]);
			j = i;
			while (j < vlist->list_len - 1)
			{
				vlist->list[j] = vlist->list[j + 1];
				j++;
			}
			vlist->list[--vlist->list_len] = NULL;
		}
		i++;
	}
	return (0);
}

int	update_env(char *name, char *value)
{
	if (name == 0 || *name == 0 || ft_strchr(name, '='))
		return (errno = EINVAL, -1);
	delete_env(name);
	bind_variable(sh_strdup(name), sh_strdup(value), (ATT_EXPORT));
	return (0);
}

void	add_exported(char *str, int append)
{
	char	*name;
	char	*value;
	int		attributes;
	char	*eq;

	(void)append;
	attributes = ATT_READONLY;
	if (str == 0 || *str == 0)
		return ;
	eq = ft_strchr(str, '=');
	if (eq == 0)
	{
		name = sh_strdup(str);
		value = sh_strdup("");
	}
	else
	{
		*eq = '\0';
		name = sh_strdup(str);
		value = sh_strdup(eq + 1);
		attributes = ATT_EXPORT;
	}
	if (attributes == ATT_EXPORT)
		delete_env(name);
	bind_variable(name, value, attributes);
}
