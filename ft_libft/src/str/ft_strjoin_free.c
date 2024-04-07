/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:49:16 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 10:49:28 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_strs(char **s1, char **s2, char *ret)
{
	if (s1 != NULL && *s1 != NULL)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 != NULL && *s2 != NULL)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (ret);
}

char	*ft_strjoin_free(char **s1, char **s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (*s1 == NULL)
		return (*s2);
	if (*s2 == NULL)
		return (*s1);
	len_s1 = ft_strlen(*s1);
	len_s2 = ft_strlen(*s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (str == NULL)
		return (free_strs(s1, s2, NULL));
	ft_strlcpy(str, *s1, len_s1 + 1);
	ft_strlcpy(str + len_s1, *s2, len_s2 + 1);
	return (free_strs(s1, s2, str));
}
