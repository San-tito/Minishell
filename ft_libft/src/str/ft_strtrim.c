/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:05:29 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:26:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_inside_set(char c, char const *set)
{
	if (set == NULL)
		return (0);
	while (*set != '\0' && c != *set)
		set++;
	if (*set == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (char_inside_set(*(s1 + i), set) && *(s1 + i) != '\0')
		i++;
	j = ft_strlen(s1);
	while (char_inside_set(*(s1 + j), set) && j > 0)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
