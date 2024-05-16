/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:36:22 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/16 13:38:57 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"

static void	exitstat(t_word_list *list)
{
	size_t	status;

	if (list && list->word[0] == '-' && list->word[1] == '-' && !list->word[2])
		list = list->next;
	if (list == 0)
		exit(g_last_exit_value);
	if (list->word == 0 || legal_number(list->word, &status) == 0)
		return (internal_error("%s: %s: %s", "exit", list->word,
				"numeric argument required"), exit(EX_BADUSAGE));
	if (list->next)
		return (internal_error("%s: %s", "exit", "too many arguments"));
	exit(status);
}

int	exit_builtin(t_word_list *list)
{
	ft_putendl_fd("exit", 2);
	return (exitstat(list), g_last_exit_value);
}
