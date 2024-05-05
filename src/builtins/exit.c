/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:36:22 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/05 21:06:40 by sguzman          ###   ########.fr       */
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
		return (g_last_exit_value);
	/* arg = list->word;
	if (arg == 0 || legal_number(arg, &sval) == 0)
	{
		sh_neednumarg(list->word->word ? list->word->word : "`'");
		return (EX_BADUSAGE);
	}
	no_args(list->next);
	status = sval & 255;
	return (status);
	*/
	return (status = ft_atoi(list->word));
}

int	exit_builtin(t_word_list *list)
{
	int	exit_value;

	exit_value = get_exitstat(list);
	g_last_exit_value = exit_value;
	exit(exit_value);
}
