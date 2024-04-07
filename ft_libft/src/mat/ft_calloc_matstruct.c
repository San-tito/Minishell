/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_matstruct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:59:13 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:59:23 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_calloc_matstruct(size_t memsize, int rows, int cols)
{
	void	**mat;
	int		i;

	if (rows < 1 || cols < 1 || memsize < 1)
		return (NULL);
	mat = malloc((rows + 1) * sizeof(void *));
	if (mat == NULL)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		*(mat + i) = malloc(memsize * (cols + 1));
		if (*(mat + i) == NULL)
		{
			ft_matclear(&mat);
			return (NULL);
		}
		i++;
	}
	*(mat + rows) = NULL;
	return (mat);
}
