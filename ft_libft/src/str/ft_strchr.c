/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:52:15 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:52:31 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	count;

	if (s == NULL)
		return (NULL);
	count = 0;
	while (*(s + count) != (char)c && *(s + count) != '\0')
		count++;
	if (*(s + count) == (char)c)
		return ((char *)(s + count));
	return (NULL);
}
