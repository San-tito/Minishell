/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:44:40 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:45:02 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenchr(char *str, char c)
{
	size_t	count;

	if (str == NULL)
		return (0);
	count = 0;
	if (c == '\0')
	{
		while (*(str + count) != '\0')
			count++;
	}
	else
	{
		while (*(str + count) != '\0' && *(str + count) != c)
			count++;
	}
	if (*(str + count) == c)
		return (count);
	return (0);
}
