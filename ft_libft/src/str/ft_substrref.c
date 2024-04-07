/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:50 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substrref(char **s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	size;

	if (*s == NULL)
		return (NULL);
	s_len = ft_strlen(*s);
	if (start > s_len)
		size = 1;
	else if (len > s_len - start)
		size = s_len - start + 1;
	else
		size = len + 1;
	str = malloc(sizeof(char) * size);
	if (str == NULL)
	{
		free(*s);
		*s = NULL;
		return (NULL);
	}
	ft_strlcpy(str, (*s) + start, size);
	return (str);
}
