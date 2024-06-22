/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:44:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 16:50:33 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	show_variable_list(void)
{
	return (0);
}

static int	is_legal(char *name, int *append)
{
	int		i;
	int		len;
	char	*assign;

	if (!name || !*name || ft_isalpha(*name) == 0)
		return (0);
	len = ft_strlen(name);
	assign = ft_strchr(name, '=');
	if (assign)
	{
		len = assign - name;
		if (name[assign - name - 1] == '+')
		{
			len = assign - name - 1;
			*append = 1;
		}
	}
	i = 1;
	while (*(name + i) && i < len)
	{
		if ((ft_isalnum(*(name + i)) || *(name + i) == '_') == 0)
			return (0);
		i++;
	}
	return (1);
}

int	export_builtin(t_word_list *list)
{
	int		result;
	int		append;
	char	*name;

	append = 0;
	result = EXECUTION_SUCCESS;
	if (list)
	{
		while (list)
		{
			name = list->word;
			if (is_legal(name, &append) == 0)
			{
				internal_error("%s: `%s': not a valid identifier", "export",
					name);
				result = EXECUTION_FAILURE;
			}
			else
				add_exported(name, append);
			list = list->next;
		}
	}
	else
		show_variable_list();
	return (result);
}
