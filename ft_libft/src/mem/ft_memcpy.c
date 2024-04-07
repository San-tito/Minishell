/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:47:30 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:47:45 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mem_overlap(const void *s1, const void *s2, size_t n)
{
	size_t		count;

	count = 0;
	while (count < n)
	{
		if ((s1 + count) == s2)
			return (1);
		count++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*ptr_dest;
	unsigned const char	*ptr_src;

	if (dest == (void *)0 && src == (void *)0 && n != 0)
		return ((void *)0);
	if (dest > src && mem_overlap(src, dest, n))
		return (ft_memmove(dest, src, n));
	else if (mem_overlap(dest, src, n))
		return (ft_memmove(dest, src, n));
	count = 0;
	ptr_dest = dest;
	ptr_src = src;
	while (count < n)
	{
		*(ptr_dest + count) = *(ptr_src + count);
		count++;
	}
	return (dest);
}
