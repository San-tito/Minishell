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

static char	*free_strs(char **s1, char **s2)
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
	return (NULL);
}

static char	*get_line(char **str, int fd)
{
	char	*buff;
	int		r;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (free_strs(str, NULL));
	r = read(fd, buff, BUFFER_SIZE);
	if (r != -1)
		*(buff + r) = '\0';
	while (r == BUFFER_SIZE && ft_strchr(buff, '\n') == NULL)
	{
		*str = ft_strjoin_free(str, &buff);
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL || str == NULL)
			return (free_strs(str, &buff));
		r = read(fd, buff, BUFFER_SIZE);
		if (r != -1)
			*(buff + r) = '\0';
	}
	if (r == -1)
		return (free_strs(str, &buff));
	*(buff + r) = '\0';
	return (ft_strjoin_free(str, &buff));
}

char	*get_next_line(int fd, char clear)
{
	static char	*str[MAX_FD] = {NULL};
	char		*tmp;
	size_t		next_newline;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= MAX_FD)
		return (NULL);
	if (clear)
	{
		free(str[fd]);
		return (NULL);
	}
	if (ft_strchr(str[fd], '\n') == NULL)
		str[fd] = get_line(&str[fd], fd);
	if (ft_strchr(str[fd], '\n') == NULL)
		return (ft_strdup_free(&str[fd], 0, NULL));
	next_newline = ft_strlenchr(str[fd], '\n');
	tmp = ft_substrref(&str[fd], 0, next_newline + 1);
	str[fd] = ft_strdup_free(&str[fd], next_newline + 1, &tmp);
	return (tmp);
}
