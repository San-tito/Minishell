/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:44:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/28 19:03:14 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	legal_identifier(char *name)
{
	int			append;
	char		*assign;
	const char	*s;

	append = 0;
	assign = ft_strchr(name, '=');
	if (assign)
	{
		name[assign - name] = '\0';
		if (name[assign - name - 1] == '+')
		{
			append++;
			name[assign - name - 1] = '\0';
		}
	}
	if (!name || !*name || (ft_isalpha(*name) || (*name == '_')) == 0)
		return (0);
	s = name + 1;
	while (*s)
	{
		if ((ft_isalnum(*s) || *s == '_') == 0)
			return (0);
		s++;
	}
	if (assign)
	{
		name[assign - name] = '=';
		if (append)
			name[assign - name - 1] = '+';
	}
	return (1);
}

int	export_builtin(t_word_list *list)
{
	int		result;
	char	*name;

	result = EXECUTION_SUCCESS;
	if (list)
	{
		while (list)
		{
			name = list->word;
			if (legal_identifier(name) == 0)
			{
				internal_error("%s: `%s': not a valid identifier", "export",
					name);
				result = EXECUTION_FAILURE;
				list = list->next;
				continue ;
			}
			add_or_replace_exported_var(name);
			list = list->next;
		}
	}
	return (result);
}
