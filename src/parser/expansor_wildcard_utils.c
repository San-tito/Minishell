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
#include "tokenizer_utils.h"

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

static void	add_match(char *match, t_list **environment_vars, char hidden_dir)
{
	char	*dup;

	if (!hidden_dir)
	{
		if (*match == '.')
			return ;
	}
	dup = sh_strdup(match);
	add_token(STR_TOKEN, dup, environment_vars);
}

void	get_matches(char *pattern, t_list **environment_vars)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = sh_opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_match(pattern, entry->d_name) == MATCH)
			add_match(entry->d_name, environment_vars, *pattern == '.');
		entry = readdir(dir);
	}
	closedir(dir);
}

void	append_content_before(char **content_before, t_list **environment_vars)
{
	t_token	*token;
	char	*new_content;

	if (*content_before == NULL)
		return ;
	if (*environment_vars != NULL)
	{
		token = (t_token *)((*environment_vars)->content);
		new_content = sh_strjoin(*content_before, token->content);
		free(*content_before);
		free(token->content);
		token->content = new_content;
	}
	else
		add_token(STR_TOKEN, *content_before, environment_vars);
}
