/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_wildcard_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_utils.h"

static char	is_match(const char *pattern, char *entry)
{
	if (!*pattern && !*entry)
		return (MATCH);
	if (*pattern == '*' && !(*(pattern + 1)))
		return (MATCH);
	if (!*pattern && *entry)
		return (NO_MATCH);
	if (*pattern == '*')
		return (is_match(pattern + 1, entry) == MATCH
			|| (*entry && is_match(pattern, entry + 1) == MATCH));
	if (*pattern == *entry)
		return (is_match(pattern + 1, entry + 1));
	return (NO_MATCH);
}

static void	add_match(char **results, char *match, char *is_first, char c)
{
	char	*dup;
	char	*space;

	if (c != '.')
	{
		if (*match == '.')
			return ;
	}
	dup = sh_strdup(match);
	if (*is_first == 1)
	{
		space = NULL;
		*is_first = 0;
	}
	else
		space = sh_strdup(" ");
	join_and_free(&space, &dup);
	join_and_free(results, &space);
}

static char	*get_matches(char **pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*results;
	char			is_first;

	is_first = 1;
	dir = opendir("."); //could this throw an error??
	if (!dir)
		return (NULL);
	results = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_match(*pattern, entry->d_name) == MATCH)
			add_match(&results, entry->d_name, &is_first, **pattern);
		entry = readdir(dir);
	}
	closedir(dir);
	if (results != NULL)
	{
		free(*pattern);
		return (results);
	}
	return (*pattern);
}

void	expand_matches(char **content, char **new_content,
	t_content_data *cont_data)
{
	char	*pattern;

	while (**content && !(**content == ' ' && !cont_data->single_q
			&& !cont_data->double_q))
	{
		if (**content == '\'' && !cont_data->double_q)
			cont_data->single_q = !cont_data->single_q;
		else if (**content == '\"' && !cont_data->single_q)
			cont_data->double_q = !cont_data->double_q;
		(*content)++;
		cont_data->len++;
	}
	pattern = ft_substr(cont_data->start, 0, cont_data->len); //change to sh_substr
	pattern = get_matches(&pattern);
	join_and_free(new_content, &pattern);
}
