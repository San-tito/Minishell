/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:44:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/28 23:20:03 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	legal_identifier(char *name)
{
	int		i;
	int		len;
	char	*assign;

	if (!name || !*name || (ft_isalpha(*name) || (*name == '_')) == 0)
		return (0);
	len = ft_strlen(name);
	assign = ft_strchr(name, '=');
	if (assign)
	{
		len = assign - name;
		if (name[assign - name - 1] == '+')
			len = assign - name - 1;
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

