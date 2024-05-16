/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/16 13:55:19 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_environ(char *envstr)
{
	char	**ep;
	size_t	size;
	//char	**new_environ;

	ep = environ;
	size = 0;
	while (ep[size])
		size++;
	// new_environ = realloc(environ, (size + 2) * sizeof(char *));
	// ft_memcpy(new_environ, environ, size * sizeof(char *));
	environ[size] = envstr;
	environ[size + 1] = NULL;
	return (0);
}

int	unset_var(const char *name)
{
	size_t	len;
	char	**ep;
	char	**sp;

	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	len = ft_strlen(name);
	ep = environ;
	while (*ep)
	{
		if (ft_strncmp(*ep, name, len) == 0 && (*ep)[len] == '=')
		{
			sp = ep;
			while (*sp)
			{
				*sp = *(sp + 1);
				sp++;
			}
		}
		else
			ep++;
	}
	return (0);
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
	add_to_environ(assign);
	return (environ);
}

void	update_env(const char *env_prefix, const char *value)
{
	char	*evar;
	int		preflen;
	int		valuelen;

	valuelen = 0;
	if (value)
		valuelen = ft_strlen(value);
	preflen = ft_strlen(env_prefix);
	evar = sh_malloc(valuelen + preflen + 1);
	ft_strlcpy(evar, env_prefix, preflen + 1);
	if (value)
		ft_strlcpy(evar + preflen, value, valuelen + 1);
	environ = add_or_replace_exported_var(evar);
}
