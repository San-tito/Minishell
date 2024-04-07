/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:04:09 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:04:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	size;

	if (s == NULL)
		size = 1;
	else
	{
		s_len = ft_strlen(s);
		if (start > s_len)
			size = 1;
		else if (len > s_len - start)
			size = s_len - start + 1;
		else
			size = len + 1;
	}
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (start > s_len)
		*str = '\0';
	else
		ft_strlcpy(str, s + start, size);
	return (str);
}
