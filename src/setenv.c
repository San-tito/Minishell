/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 20:03:39 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	unset_multiple_times(const char *name, int len, int offset)
{
	char	**p;

	while (find_env(name, len, &offset))
	{
		p = environ + offset - 1;
		while (*p++)
			*p = *(p + 1);
	}
}

int	delete_env(const char *name)
{
	int	offset;

	offset = 0;
	if (name == 0 || *name == 0 || ft_strchr(name, '='))
		return (errno = EINVAL, -1);
	unset_multiple_times(name, ft_strlen(name), offset);
	return (0);
}

void	last_environ(void (*cleanup_func)(void *))
{
	size_t		cnt;
	char		**p;
	static char	**lastenv;

	if (cleanup_func)
		return (cleanup_func(lastenv));
	cnt = 0;
	if (environ)
	{
		p = environ;
		while (*p)
			p++;
		cnt = p - environ;
	}
	p = sh_realloc(lastenv, (cnt + 2) * sizeof(char *));
	if (lastenv != environ && environ)
		ft_memcpy(p, environ, cnt * sizeof(char *));
	environ = p;
	lastenv = environ;
	environ[cnt + 1] = 0;
}

int	update_env(const char *name, const char *value)
{
	int	tmpoff;
	int	offset;

	offset = 0;
	if (name == 0 || *name == 0 || ft_strchr(name, '='))
		return (errno = EINVAL, -1);
	if (find_env(name, ft_strlen(name), &offset))
	{
		tmpoff = offset + 1;
		unset_multiple_times(name, ft_strlen(name), tmpoff);
	}
	else
	{
		last_environ(0);
		while (environ[offset])
			offset++;
	}
	environ[offset] = sh_malloc(ft_strlen(name) + ft_strlen(value) + 2);
	ft_memcpy(environ[offset], name, ft_strlen(name));
	environ[offset][ft_strlen(name)] = '=';
	ft_memcpy(environ[offset] + ft_strlen(name) + 1, value, ft_strlen(value)
		+ 1);
	return (0);
}

int	add_exported(char *name, int append)
{
	int	offset;
	int	len;

	(void)append;
	if (name == 0 || *name == 0)
		return (errno = EINVAL, -1);
	len = ft_strlen(name);
	if (ft_strchr(name, '='))
		len = ft_strchr(name, '=') - name;
	offset = 0;
	unset_multiple_times(name, len, offset);
	return (0);
}
