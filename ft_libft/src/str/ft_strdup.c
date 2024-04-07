/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:02:24 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:02:37 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*src_cpy;
	size_t	length;

	length = ft_strlen(s);
	src_cpy = malloc(sizeof(char) * (length + 1));
	if (src_cpy == NULL)
		return (NULL);
	ft_strlcpy(src_cpy, s, length + 1);
	return (src_cpy);
}
