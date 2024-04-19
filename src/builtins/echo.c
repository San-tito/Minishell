/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:41:45 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:56:56 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	echo_builtin(t_word_list *list)
{
	char	*temp;
	int		display_nl;

	display_nl = 1;
	while (list && *list->word == '-')
	{
		temp = list->word;
		while (*temp++)
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
		if (temp)
			printf("%s", temp);
		list = list->next;
		if (list)
			printf("%c", ' ');
	}
	if (display_nl)
		printf("%c", '\n');
	return (EXECUTION_SUCCESS);
}
