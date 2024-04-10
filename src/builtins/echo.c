/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:41:45 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/10 23:29:32 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_word_list *list)
{
	char	*temp;
	int		i;
	int		display_nl;

	display_nl = 1;
	while (list && *list->word == '-')
	{
		temp = list->word + 1;
		i = 0;
		while (temp[i])
		{
			if (ft_strchr("n", temp[i]) == 0)
				break ;
			i++;
		}
		if (*temp == 0 || temp[i])
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
