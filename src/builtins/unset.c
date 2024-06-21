/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:35:26 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 19:48:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		delete_env(name);
		list = list->next;
	}
	return (result);
}
