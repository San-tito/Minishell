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
#include "variables.h"

static char	*obtain_word_to_expand(char **content)
{
	char	*start;
	int		len;

	start = *content;
	len = 0;
	while (**content != ' ' && **content != '$' && **content != '\''
		&& **content != '\"' && **content)
	{
		(*content)++;
		len++;
	}
	return (sh_substr(start, 0, len));
}

void	join_and_free(char **str, char **str_to_add)
{
	char	*word;

	if (*str == NULL)
		*str = *str_to_add;
	else
	{
		word = sh_strjoin(*str, *str_to_add);
		if (*str_to_add != NULL)
			free(*str_to_add);
		free(*str);
		*str = word;
	}
}

/*
 *	Expands the value of an environmental variable.
 */
void	expand_value(char **new_content, char **content)
{
	char	*word;
	char	*value_expanded;

	(*content)++;
	if (**content == '?')
	{
		value_expanded = sh_itoa(g_last_exit_value);
		(*content)++;
	}
	else
	{
		word = obtain_word_to_expand(content);
		value_expanded = find_env(word);
		free(word);
		if (value_expanded == NULL)
			return ;
		value_expanded = sh_strdup(value_expanded);
	}
	join_and_free(new_content, &value_expanded);
}

void	append_content(char **new_content, t_content_data content_data)
{
	char	*word;

	if (content_data.len == 0)
		return ;
	word = sh_substr(content_data.start, 0, content_data.len);
	join_and_free(new_content, &word);
}

void	finalize_content(t_token *token, char **new_content,
	t_content_data content_data)
{
	append_content(new_content, content_data);
	free(token->content);
	token->content = *new_content;
}
