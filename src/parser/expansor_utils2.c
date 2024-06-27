/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils2.c                                  :+:      :+:    :+:   */
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

static void	expand_and_append(char **env_var, char **content_before,
	t_list **environment_vars, t_content_data *content_data)
{
	char	*value;

	value = find_env(*env_var);
	if (value != NULL)
		value = sh_strdup(value);
	free(*env_var);
	append_env_vars(&value, content_before, environment_vars, content_data);
}

static void	handle_ascii(char **content, char **content_before,
	t_list **environment_vars, t_content_data *content_data)
{
	char	*ascii_str;

	if (**content == '\'')
		content_data->single_q = !content_data->single_q;
	else
		content_data->double_q = !content_data->double_q;
	(*content)++;
	while ((content_data->single_q && **content != '\'')
		|| (content_data->double_q && **content != '\"'))
	{
		(*content)++;
		content_data->len++;
	}
	ascii_str = sh_substr(content_data->start, 1, content_data->len);
	content_data->start += content_data->len + 2;
	(*content)++;
	content_data->len = 0;
	if (content_data->single_q)
		content_data->single_q = !content_data->single_q;
	else
		content_data->double_q = !content_data->double_q;
	append_env_vars(&ascii_str, content_before, environment_vars, content_data);
}

static void	expand_special_cases(char **content, char **content_before,
	t_list **environment_vars, t_content_data *content_data)
{
	char	*value;

	if (**content == '?')
	{
		value = sh_itoa(g_last_exit_value);
		(*content)++;
		content_data->start++;
		append_env_vars(&value, content_before, environment_vars, content_data);
	}
	else if (**content == '$')
	{
		value = sh_itoa(42);
		(*content)++;
		content_data->start++;
		append_env_vars(&value, content_before, environment_vars, content_data);
	}
	else if ((**content == '\'' || **content == '\"')
		&& !content_data->single_q && !content_data->double_q)
		handle_ascii(content, content_before, environment_vars, content_data);
	else
	{
		value = sh_strdup("$");
		append_env_vars(&value, content_before, environment_vars, content_data);
	}
}

static char	*obtain_name(char **content, t_content_data *content_data)
{
	char	*env_var;

	while (**content != ' ' && **content != '\0' && **content != '\"'
		&& **content != '\'' && **content != '$')
	{
		content_data->len++;
		(*content)++;
	}
	env_var = sh_substr(content_data->start, 0, content_data->len);
	content_data->start += content_data->len;
	content_data->len = 0;
	return (env_var);
}

/*
 *	The character that content is pointing to is '$'.
 *	We store the content before '$' into another string (content_before).
 *	We check special cases ($?, $$ or even $) and if not we obtain
 *	the name of the env var to expand.
 *	Then we obtain the environment value.
 */
void	expand_env_var(char **content, t_content_data *content_data,
	t_list **environment_vars)
{
	char	*content_before;
	char	*env_var;

	(*content)++;
	content_before = NULL;
	if (content_data->len != 0)
	{
		content_before = sh_substr(content_data->start, 0, content_data->len);
		content_data->start += content_data->len;
		content_data->len = 0;
	}
	content_data->start++;
	if (**content == '?' || **content == '$' || **content == ' '
		|| **content == '\'' || **content == '\"' || **content == '\0')
	{
		expand_special_cases(content, &content_before,
			environment_vars, content_data);
		return ;
	}
	env_var = obtain_name(content, content_data);
	expand_and_append(&env_var, &content_before,
		environment_vars, content_data);
}
