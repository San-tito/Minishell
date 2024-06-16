/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_utils.h"
#include "execute_cmd.h"

static char	*obtain_word_to_expand(char **content, char **new_content)
{
	char	*start;
	int		len;
	char	*word;

	start = *content;
	len = 0;
	while (**content != ' ' && **content != '\'' && **content
		!= '\"' && **content)
	{
		(*content)++;
		len++;
	}
	word = ft_substr(start, 0, len);
	if (word == NULL)
	{
		if (*new_content != NULL)
			free(*new_content);
		return (NULL);
	}
	return (word);
}

char	join_and_free(char **str, char **str_to_add)
{
	char	*word;

	if (*str == NULL)
		*str = *str_to_add;
	else
	{
		word = ft_strjoin(*str, *str_to_add);
		if (*str_to_add != NULL)
			free(*str_to_add);
		free(*str);
		if (word == NULL)
			return (ERROR);
		*str = word;
	}
	return (CORRECT);
}

/*
 *	Expands the value of an environmental variable.
 */
char	expand_value(char **new_content, char **content)
{
	char	*word;
	char	*value_expanded;

	(*content)++;
	if (**content == '?')
	{
		value_expanded = ft_itoa(g_last_exit_value);
		(*content)++;
	}
	else
	{
		word = obtain_word_to_expand(content, new_content);
		if (word == NULL)
			return (ERROR);
		value_expanded = getenv(word);
		free(word);
		if (value_expanded == NULL)
			return (CORRECT);
		value_expanded = ft_strdup(value_expanded);
	}
	if (value_expanded == NULL)
		return (ERROR);
	return (join_and_free(new_content, &value_expanded));
}

char	append_content(char **new_content, t_content_data content_data)
{
	char	*word;

	if (content_data.len == 0)
		return (CORRECT);
	word = ft_substr(content_data.start, 0, content_data.len);
	if (word == NULL)
	{
		if (*new_content != NULL)
			free(*new_content);
		return (ERROR);
	}
	return (join_and_free(new_content, &word));
}
