/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:18:39 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 18:15:16 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_word_list *list)
{
	int			i;
	t_varlist	*vlist;

	(void)list;
	i = 0;
	vlist = varlist();
	while (i < vlist->list_len)
	{
		if (vlist->list[i]->attributes & ATT_EXPORT)
			ft_printf("%s=%s\n", vlist->list[i]->name, vlist->list[i]->value);
		i++;
	}
	return (EXECUTION_SUCCESS);
}
