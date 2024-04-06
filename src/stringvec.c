/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringvec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:47:32 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 00:28:02 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strvec_from_word_list(t_word_list *list)
{
	int		count;
	char	**array;

	count = list_length(list);
	array = sh_malloc((1 + count) * sizeof(char *));
	count = 0;
	while (list)
	{
		array[count] = list->word;
		list = list->next;
		count++;
	}
	array[count] = NULL;
	return (array);
}
