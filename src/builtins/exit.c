/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:36:22 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/13 18:48:29 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"

int	exit_builtin(t_word_list *list)
{
	int	exit_value;

	ft_putendl_fd("exit", 2);
	if (list && list->word[0] == '-' && list->word[1] == '-' && !list->word[2])
		list = list->next;
	if (list == 0)
		return (g_last_exit_value);
	if (list->word == 0 || legal_number(list->word, &exit_value) == 0)
		return (internal_error("%s: %s: %s", "exit", list->word,
				"numeric argument required"), EX_BADUSAGE);
	if (list->next)
		return (internal_error("%s: %s", "exit", "too many arguments"),
			g_last_exit_value);
	g_last_exit_value = exit_value;
	exit(exit_value);
}
