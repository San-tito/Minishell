/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:06:50 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 16:50:55 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t bytes)
{
	void	*temp;

	temp = malloc(bytes);
	if (temp == 0)
		return (0);
	return (temp);
}

void	ft_free(void *string)
{
	if (string)
		free(string);
	string = NULL;
}

void	ft_double_free(void **array)
{
	void	**ptr;

	ptr = array;
	while (*ptr)
		ft_free(*ptr++);
	ft_free(array);
}
