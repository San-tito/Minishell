/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:59:13 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:59:23 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matclear(void ***mat)
{
	size_t	i;
	void	**tmp;

	tmp = *mat;
	i = 0;
	while (*(tmp + i) != NULL)
	{
		free(*(tmp + i));
		i++;
	}
	free(*mat);
}
