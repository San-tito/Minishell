/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:09:36 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 16:54:06 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*sh_malloc(size_t bytes)
{
	void	*temp;

	temp = malloc(bytes);
	if (temp == 0)
		fatal_error("%s: cannot allocate %lu bytes", "sh_malloc",
			(unsigned long)bytes);
	return (temp);
}

void	sh_free(void *string)
{
	if (string)
		free(string);
}

void	*sh_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == 0)
		return (sh_malloc(size));
	new_ptr = sh_malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	sh_free(ptr);
	return (new_ptr);
}

void	sh_doublefree(void **array)
{
	void	**ptr;

	ptr = array;
	while (*ptr)
		sh_free(*ptr++);
	sh_free(array);
}

char	*sh_strdup(char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (dup == NULL)
		fatal_error("Not enough memory to duplicate %s", str);
	return (dup);
}
