/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:59:13 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:59:23 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;

	i = 0;
	while (i < n && *(unsigned const char *)(s + i) != (unsigned char)c)
		i++;
	if (i < n && *(unsigned const char *)(s + i) == (unsigned char)c)
		return ((void *)(s + i));
	return (NULL);
}
