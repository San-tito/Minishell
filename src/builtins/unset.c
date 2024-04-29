/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:35:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/29 11:29:23 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	legal_identifier(char *name)
{
	char	*s;

	if (!name || !*name || (ft_isalpha(*name) || (*name == '_')) == 0)
		return (0);
	s = name + 1;
	while (*s)
	{
		if ((ft_isalnum(*s) || *s == '_') == 0)
			return (0);
		s++;
	}
	return (1);
}

int	unset_builtin(t_word_list *list)
{
	int		result;
	char	*name;

	result = EXECUTION_SUCCESS;
	while (list)
	{
		name = list->word;
		if (legal_identifier(name) == 0)
		{
			internal_error("%s: `%s': not a valid identifier", "unset", name);
			result = EXECUTION_FAILURE;
			list = list->next;
			continue ;
		}
		unset_var(name);
		list = list->next;
	}
	return (result);
}
