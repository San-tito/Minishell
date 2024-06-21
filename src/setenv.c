/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:55:43 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 14:20:36 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdint.h>

char	*__findenv(const char *name, int len, int *offset)
{
	int			i;
	const char	*np;

	char **p, *cp;
	if (name == NULL || environ == NULL)
		return (NULL);
	for (p = environ + *offset; (cp = *p) != NULL; ++p)
	{
		for (np = name, i = len; i && *cp; i--)
			if (*cp++ != *np++)
				break ;
		if (i == 0 && *cp++ == '=')
		{
			*offset = p - environ;
			return (cp);
		}
	}
	return (NULL);
}

int	add_to_environ(char *envstr)
{
	char	**ep;
	size_t	size;

	ep = environ;
	size = 0;
	while (ep[size])
		size++;
	environ[size++] = envstr;
	environ[size] = NULL;
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
	char		*new_value;
	const char	*equal_offset = ft_strchr(assign, '=');

	if (equal_offset == 0)
		return (environ);
	i = 0;
	new_value = sh_malloc(ft_strlen(assign) + 1);
	ft_strlcpy(new_value, assign, ft_strlen(assign) + 1);
	while (environ[i])
	{
		if (ft_strncmp(assign, environ[i], equal_offset - assign) == 0)
		{
			environ[i] = new_value;
			return (environ);
		}
		i++;
	}
	add_to_environ(new_value);
	return (environ);
}

int	update_env(const char *name, const char *value)
{
	const char	*np;
	int			tmpoff;
	size_t		cnt;

	char *C, **P;
	int l_value, offset = 0;
	if (!name || !*name)
	{
		errno = EINVAL;
		return (-1);
	}
	for (np = name; *np && *np != '='; ++np)
		;
	if (*np)
	{
		errno = EINVAL;
		return (-1); /* has `=' in name */
	}
	l_value = strlen(value);
	if ((C = __findenv(name, (int)(np - name), &offset)) != NULL)
	{
		tmpoff = offset + 1;
		/* could be set multiple times */
		while (__findenv(name, (int)(np - name), &tmpoff))
		{
			for (P = &environ[tmpoff];; ++P)
				if (!(*P = *(P + 1)))
					break ;
		}
	}
	else
	{ /* create new slot */
		cnt = 0;
		if (environ != NULL)
		{
			for (P = environ; *P != NULL; P++)
				;
			cnt = P - environ;
		}
		P = sh_realloc(environ, (cnt + 2) * sizeof(char *));
		if (!P)
			return (-1);
		if (environ != NULL)
			memcpy(P, environ, cnt * sizeof(char *));
		environ = P;
		offset = cnt;
		environ[cnt + 1] = NULL;
	}
	if (!(environ[offset] = /* name + `=' + value */
			malloc((int)(np - name) + l_value + 2)))
		return (-1);
	for (C = environ[offset]; (*C = *name++) && *C != '='; ++C)
		;
	for (*C++ = '='; (*C++ = *value++);)
		;
	return (0);
}
