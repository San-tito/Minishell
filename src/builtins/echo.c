/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:41:45 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/10 19:38:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_word_list *list)
{
	char	*temp;
	int		display_nl;

	display_nl = 1;
	temp = list->word;
	while (list && *temp == '-')
	{
		temp++;
		if (ft_strchr(temp, 'n') == 0)
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
