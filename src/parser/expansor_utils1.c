/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_utils.h"
#include "tokenizer_utils.h"

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
 *	If environment_vars is not NULL we append content to the last node
 *	of environment_vars.
 *	If it is NULL, we create a new node.
 */
void	create_concat_node(char **content, t_list **environment_vars)
{
	char	*new_value;
	t_list	*last;
	t_token	*token;

	if (*environment_vars != NULL)
	{
		last = ft_lstlast(*environment_vars);
		token = (t_token *)(last->content);
		new_value = sh_strjoin(token->content, *content);
		free(token->content);
		free(*content);
		token->content = new_value;
	}
	else
		add_token(STR_TOKEN, *content, environment_vars);
}

void	append_last_chars(t_list **environment_vars,
	t_content_data content_data, char expanded)
{
	t_list	*node;
	char	*new_content;
	char	*last_content;
	t_token	*token;

	if (content_data.len != 0 && expanded == EXPANDED)
	{
		last_content = sh_substr(content_data.start, 0, content_data.len);
		if (*environment_vars != NULL)
		{
			node = ft_lstlast(*environment_vars);
			token = (t_token *)(node->content);
			new_content = sh_strjoin(token->content, last_content);
			free(last_content);
			free(token->content);
			token->content = new_content;
		}
		else
			create_concat_node(&last_content, environment_vars);
	}
}

/*
 *	Not free value bc it gets freed outside.
 */
static void	add_all_tokens(char *value, char **content_before,
	t_list **environment_vars)
{
	char	**matrix;
	int		i;

	if (*value == '\0')
	{
		if (*content_before == NULL)
			*content_before = sh_strdup(value);
		create_concat_node(content_before, environment_vars);
		return ;
	}
	matrix = ft_split(value, ' '); //change to sh_split
	if (*content_before != NULL)
		join_and_free(content_before, matrix);
	else
		*content_before = *matrix;
	create_concat_node(content_before, environment_vars);
	i = 1;
	while (*(matrix + i))
	{
		add_token(STR_TOKEN, *(matrix + i), environment_vars);
		i++;
	}
	free(matrix);
}

/*
 *	We append the value expanded into our "local" t_list of tokens.
 *	Based on the value expanded:
 *	-If there is none, we create a new node with content_before as content.
 *	-If there is, if we are in double quotes we join content_before and
 *	the environment value obtained.
 *	-If we are not in double quotes, we create a node for each space
 *	inside env variable and then join from the start content_before to
 *	the first node.
 */
void	append_env_vars(char **value, char **content_before,
	t_list **environment_vars, t_content_data *content_data)
{
	char	*new_value;

	if (*value == NULL)
	{
		if (*content_before != NULL)
			add_token(STR_TOKEN, *content_before, environment_vars);
	}
	else if (content_data->double_q)
	{
		if (*content_before != NULL)
		{
			new_value = sh_strjoin(*content_before, *value);
			free(*content_before);
			free(*value);
		}
		create_concat_node(&new_value, environment_vars);
	}
	else
	{
		add_all_tokens(*value, content_before, environment_vars);
		free(*value);
	}
}
