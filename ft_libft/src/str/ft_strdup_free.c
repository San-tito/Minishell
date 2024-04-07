/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:14:00 by mpovill-          #+#    #+#             */
/*   Updated: 2023/10/12 16:22:21 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_strs(char **s1, char **s2, char **s3)
{
	if (s1 != NULL && *s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (*s2 != NULL)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 != NULL && *s3 != NULL)
	{
		free(*s3);
		*s3 = NULL;
	}
	return (NULL);
}

char	*ft_strdup_free(char **str, size_t newline, char **tmp)
{
	char	*dup;
	size_t	length;

	if (*str == NULL)
		return (NULL);
	length = ft_strlen((*str) + newline);
	dup = malloc(sizeof(char) * (length + 1));
	if (dup == NULL)
		return (free_strs(str, &dup, tmp));
	ft_strlcpy(dup, (*str) + newline, length + 1);
	if (*dup == '\0')
		return (free_strs(str, &dup, NULL));
	free(*str);
	*str = NULL;
	return (dup);
}
