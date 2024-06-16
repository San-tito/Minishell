/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_wildcard.c                                :+:      :+:    :+:   */
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
		return (is_match(pattern + 1, entry) == MATCH || (*entry && is_match(pattern, entry + 1) == MATCH));
	if (*pattern == *entry)
		return (is_match(pattern + 1, entry + 1));
	return (NO_MATCH);
}

static void	add_match(char **results, char *match, char *is_first)
{
	char	*dup;
	char	*space;

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
	DIR		*dir;
	struct	dirent *entry;
	char	*results;
	char	is_first;

	is_first = 1;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	results = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_match(*pattern, entry->d_name) == MATCH)
			add_match(&results, entry->d_name, &is_first);
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

static char	expand_matches(char **content, char **new_content,
	t_content_data cont_data)
{
	char	*pattern;

	while (**content && !(**content == ' ' && !cont_data.single_q
		&& !cont_data.double_q))
	{
		if (**content == '\'' && !cont_data.double_q)
			cont_data.single_q = !cont_data.single_q;
		else if (**content == '\"' && !cont_data.single_q)
			cont_data.double_q = !cont_data.double_q;
		(*content)++;
		cont_data.len++;
	}
	pattern = ft_substr(cont_data.start, 0, cont_data.len);
	if (pattern == NULL)
	{
		if (*new_content != NULL)
			free(*new_content);
		return (ERROR);
	}
	pattern = get_matches(&pattern);
	return (join_and_free(new_content, &pattern));
}

static char	append_last_space(char **new_content, t_content_data cont_data)
{
	char	*word;

	if (cont_data.last_space != 0)
	{
		word = ft_substr(cont_data.start, 0, cont_data.last_space);
		if (word == NULL)
		{
			if (*new_content != NULL)
				free(*new_content);
			return (ERROR);
		}
		return (join_and_free(new_content, &word));
	}
	return (CORRECT);
}

/*
 *	Checks if the current character in content must be interpreted: '*' case.
 *	If it is not, it returns not interpreted (0).
 *	If there is an error when interpreting, it returns ERROR.
 *	If there is not an error when intrepreting, it returns interpreted (1);
 */
static char	interpret_content(char **content, char **new_content,
	t_content_data cont_data)
{
	char	currchar;

	currchar = **content;
	if (currchar == '\'' && !cont_data.double_q)
		cont_data.single_q = !cont_data.single_q;
	else if (currchar == '\"' && !cont_data.single_q)
		cont_data.double_q = !cont_data.double_q;
	else
	{
		if (currchar == ' ' && !cont_data.single_q && !cont_data.double_q)
			cont_data.last_space = cont_data.len;
		else if (currchar == '*' && !cont_data.single_q && !cont_data.double_q)
		{
			if (append_last_space(new_content, cont_data) == ERROR)
				return (ERROR);
			cont_data.start += cont_data.last_space;
			cont_data.len -= cont_data.last_space;
			cont_data.last_space = 0;
			if (expand_matches(content, new_content, cont_data) == ERROR)
				return (ERROR);
			cont_data.start = *content; // last char
			if (*content)
				cont_data.start++;
			cont_data.last_space = 0;
			cont_data.len = 0;
			return (1);
		}
	}
	return (0);
}

/*
*	Searches the content of the token for wildcards
*	and expands them.
*/
static char	handle_wildcards(t_token *token)
{
	t_content_data	content_data;
	char			*content;
	char			*new_content;
	char			interpreted;

	content_data = initialize_content(token->content, &content, &new_content);
	while (*content)
	{
		interpreted = interpret_content(&content, &new_content, content_data);
		if (interpreted == ERROR)
			return (ERROR);
		else if (!interpreted)
		{
			content++;
			content_data.len++;
		}
	}
	if (content_data.last_space == 0 && new_content != NULL)
	{
		free(token->content);
		token->content = new_content;
		return (CORRECT);
	}
	if (finalize_content(token, &new_content, content_data) == ERROR)
		return (ERROR);
	return (CORRECT);
}

/*
*	Gets a list of tokens and for each STR_TOKEN it finds
*	expands the wildcards inside of it.
*/
char	expand_wildcards(t_list **tokens)
{
	t_list	*lst;
	t_token	*token;

	lst = *tokens;
	while (lst)
	{
		token = (t_token *)(lst->content);
		if (token->type == STR_TOKEN && token->content != NULL)
			handle_wildcards(token);
		lst = lst->next;
	}
	return (CORRECT);
}
