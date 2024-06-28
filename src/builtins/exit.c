/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:36:22 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 12:49:37 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear_cmd.h"
#include "execute_cmd.h"
#include "minishell.h"

static int	exitstat(t_word_list *list, ssize_t *status)
{
	if (list && list->word[0] == '-' && list->word[1] == '-' && !list->word[2])
		list = list->next;
	if (list == 0)
	{
		*status = g_last_exit_value;
		return (0);
	}
	if (list->word == 0 || legal_number(list->word, status) == 0)
	{
		internal_error("%s: %s: %s", "exit", list->word,
			"numeric argument required");
		*status = EX_BADUSAGE;
		return (0);
	}
	if (list->next)
	{
		internal_error("%s: %s", "exit", "too many arguments");
		return (1);
	}
	*status = *status & 255;
	return (0);
}

int	exit_builtin(t_word_list *list)
{
	ssize_t	status;

	ft_putendl_fd("exit", 2);
	if (exitstat(list, &status) == 0)
		sh_exit(status);
	return (g_last_exit_value);
}
