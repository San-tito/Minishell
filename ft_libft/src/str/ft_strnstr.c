/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:00:28 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:00:43 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	searchin_big(const char *big, const char *lit, size_t i, size_t len)
{
	while (*lit != '\0' && *big != '\0' && i < len)
	{
		if (*lit != *big)
			return (0);
		lit++;
		i++;
		big++;
	}
	if (*lit == '\0')
		return (1);
	return (-1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		result;
	size_t	count;

	if (*little == '\0')
		return ((char *)big);
	count = 0;
	while (count < len && *big != '\0')
	{
		if (*big == *little)
		{
			result = searchin_big(big, little, count, len);
			if (result == 1)
				return ((char *)big);
			if (result == -1)
				return (NULL);
		}
		big++;
		count++;
	}
	return (NULL);
}
