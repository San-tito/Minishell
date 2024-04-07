/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:48:29 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:48:47 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*ptr_dest;

	if (dest == (void *)0 && src == (void *)0 && n != 0)
		return ((void *)0);
	ptr_dest = dest;
	if (dest > src)
	{
		count = n;
		while (count > 0)
		{
			count--;
			*(ptr_dest + count) = *(unsigned char *)(src + count);
		}
	}
	else
	{
		count = 0;
		while (count < n)
		{
			*(ptr_dest + count) = *(unsigned char *)(src + count);
			count++;
		}
	}
	return (dest);
}
