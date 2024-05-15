/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:36:22 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/15 16:34:28 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"

static int	get_exitstat(t_word_list *list)
{
	int	status;

	if (list && list->word[0] == '-' && list->word[1] == '-' && !list->word[2])
		list = list->next;
	if (list == 0)
		exit(g_last_exit_value);
	if (list->word == 0 || legal_number(list->word, &status) == 0)
		return (internal_error("%s: %s: %s", "exit", list->word,
				"numeric argument required"), exit(EX_BADUSAGE), EX_BADUSAGE);
	if (list->next)
		return (internal_error("%s: %s", "exit", "too many arguments"),
			g_last_exit_value);
	return (exit(status), status);
}

int	exit_builtin(t_word_list *list)
{
	ft_putendl_fd("exit", 2);
	return (g_last_exit_value = get_exitstat(list));
}
