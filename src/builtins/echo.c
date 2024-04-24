/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:41:45 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/24 23:30:56 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_word_list *list)
{
	char	*temp;
	int		display_nl;

	display_nl = 1;
	while (list && *list->word == '-')
	{
		temp = list->word;
		while (*(++temp))
			if (ft_strchr("n", *temp) == 0)
				break ;
		if (*temp || *(list->word + 1) == 0)
			break ;
		display_nl = 0;
		list = list->next;
	}
	while (list)
	{
		temp = list->word;
		ft_putstr_fd(temp, 1);
		list = list->next;
		if (list)
			ft_putchar_fd(' ', 1);
	}
	if (display_nl)
		ft_putchar_fd('\n', 1);
	return (EXECUTION_SUCCESS);
}
