/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:09:36 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 17:09:48 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*sh_malloc(size_t bytes)
{
	void	*temp;

	temp = malloc(bytes);
	if (temp == 0)
		/* Handle Error */
		return (0);
	return (temp);
}

void	sh_free(void *string)
{
	if (string)
		free(string);
	string = NULL;
}

void	sh_doublefree(void **array)
{
	void	**ptr;

	ptr = array;
	while (*ptr)
		sh_free(*ptr++);
	sh_free(array);
}
