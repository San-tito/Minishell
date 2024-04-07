/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:10:56 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:11:12 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strings(const char *str, char c)
{
	int	n_strs;
	int	n_chars;

	n_chars = 0;
	n_strs = 0;
	while (*str != '\0')
	{
		if (*str == c)
		{
			if (n_chars != 0)
			{
				n_chars = 0;
				n_strs++;
			}
			str++;
		}
		else
		{
			n_chars++;
			str++;
		}
	}
	if (n_chars != 0)
		n_strs++;
	return (n_strs);
}

static int	add_str_to_matrix(const char *str, int word, int i, char **matrix)
{
	*(matrix + i) = ft_substr(str, 0, word);
	if (*(matrix + i) == NULL)
	{
		while (i >= 0)
		{
			free(*(matrix + i));
			i--;
		}
		free(matrix);
		return (0);
	}
	return (1);
}

static int	create_matrix(const char *str, char c, int length, char **matrix)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (i < length && *(str + word) != '\0')
	{
		if (*(str + word) == c && word != 0)
		{
			if (add_str_to_matrix(str, word, i, matrix) == 0)
				return (0);
			i++;
			str = str + word;
			word = 0;
		}
		else if (*str == c)
			str++;
		else
			word++;
	}
	if (word != 0)
		if (add_str_to_matrix(str, word, i, matrix) == 0)
			return (0);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		length;
	char	**matrix;

	if (s == NULL)
		return (NULL);
	length = count_strings(s, c);
	matrix = malloc(sizeof(char *) * (length + 1));
	if (matrix == NULL)
		return (NULL);
	if (create_matrix(s, c, length, matrix) == 0)
		return (NULL);
	*(matrix + length) = NULL;
	return (matrix);
}
