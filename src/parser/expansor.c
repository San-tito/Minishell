/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansor_utils.h"
#include "variables.h"
#include "tokenizer_utils.h"
#include "execute_cmd.h"

/*
t_content_data	initialize_content(char *token_content, char **content,
	char **new_content)
{
	t_content_data	content_data;

	*content = token_content;
	*new_content = NULL;
	content_data.start = token_content;
	content_data.last_space = 0;
	content_data.len = 0;
	content_data.single_q = 0;
	content_data.double_q = 0;
	return (content_data);
}
 */

/*
 *	Checks if the current character in content must be interpreted: '$' case.
 *	If it is not, it returns not interpreted (0).
 *	If there is an error when interpreting, it returns ERROR.
 *	If there is not an error when intrepreting, it returns interpreted (1);
 */
/*
static char	interpret_content(char **content, char **new_content,
	t_content_data *content_data)
{
	if (**content == '\'' && !content_data->double_q)
		content_data->single_q = !content_data->single_q;
	else if (**content == '\"' && !content_data->single_q)
		content_data->double_q = !content_data->double_q;
	else
	{
		if (need_expand(content, content_data))
		{
			append_content(new_content, *content_data);
			content_data->len = 0;
			expand_value(new_content, content);
			content_data->start = *content;
			return (1);
		}
	}
	return (0);
}
*/

/*
*	Searches the content of the token for environmental variables
*	and expands them.
*/
/*
static t_list	*search_environment_variables(t_token *token)
{
	t_content_data	content_data;
	char			*content;
	char			*new_content;
	char			interpreted;

	content_data = initialize_content(token->content, &content, &new_content);
	while (*content)
	{
		interpreted = interpret_content(&content, &new_content, &content_data);
		if (!interpreted)
		{
			content++;
			content_data.len++;
		}
	}
	finalize_content(token, &new_content, content_data);
}
 */

static char	can_expand_env_var(char *content, t_content_data *content_data)
{
	if (*content == '\'' && !content_data->double_q)
		content_data->single_q = !content_data->single_q;
	else if (*content == '\"' && !content_data->single_q)
		content_data->double_q = !content_data->double_q;
	else if (content_data->single_q)
		return (0);
	else if (*content != '$')
		return (0);
	else if (content_data->double_q && *(content + 1) == '\"')
		return (0);
	else if (*(content + 1) == ' ' || *(content + 1) == '\0')
		return (0);
	else
		return (1);
	return (0);
}

/*
 *	Expands the value of an environmental variable.
 */
/*
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
*/

static void	add_all_tokens(char *value, char **content_before,
	t_list **environment_vars)
{
	char	**matrix;
	char	*first;
	int		i;

	matrix = ft_split(value, ' '); //change to sh_split
	if (*content_before != NULL)
	{
		first = sh_strjoin(*content_before, *matrix);
		add_token(STR_TOKEN, first, environment_vars);
		free(*content_before);
		free(*matrix);
	}
	else
		add_token(STR_TOKEN, *matrix, environment_vars);
	i = 1;
	while (*(matrix + i))
	{
		//ft_printf("Content: [%s]\n", *(matrix + i));
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
static void	append_env_vars(t_list **environment_vars, char **value,
	char **content_before, t_content_data *content_data)
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
		add_token(STR_TOKEN, new_value, environment_vars);
	}
	else
	{
		add_all_tokens(*value, content_before, environment_vars);
		free(*value);
	}
}

static void	expand_and_append(char **content_before, char **env_var,
	t_list **environment_vars, t_content_data *content_data)
{
	char	*value;

	if (**env_var == '$')
		value = sh_itoa(42);
	else if (**env_var == '?')
		value = sh_itoa(g_last_exit_value);
	else
	{
		value = find_env(*env_var);
		if (value != NULL)
			value = sh_strdup(value);
	}
	free(*env_var);
	append_env_vars(environment_vars, &value, content_before, content_data);
}

/*
 *	The character that content is pointing to is '$'.
 *	We store the content before '$' into another string (content_before).
 *	We obtaing the following string till we get to '\0' or ' '.
 *	Then we obtain the environment value.
 */
static void	expand_env_var(char **content, t_content_data *content_data,
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
	while (**content != ' ' && **content != '\0' && **content != '\"'
		&&  **content != '\'')
	{
		content_data->len++;
		(*content)++;
	}
	env_var = sh_substr(content_data->start, 0, content_data->len);
	content_data->start += content_data->len;
	content_data->len = 0;
	expand_and_append(&content_before, &env_var,
		environment_vars, content_data);
}

static void	append_last_chars(t_list *environment_vars, t_content_data content_data)
{
	t_list	*node;
	char	*new_content;
	char	*last_content;
	t_token	*token;

	if (content_data.len != 0 && environment_vars != NULL)
	{
		node = ft_lstlast(environment_vars);
		token = (t_token *)(node->content);
		last_content = sh_substr(content_data.start, 0, content_data.len);
		new_content = sh_strjoin(token->content, last_content);
		free(last_content);
		free(token->content);
		token->content = new_content;
	}
}

/*
 *	Iterates the content of a token searching the start of an environment
 *	variable ($) without being in single quotes.
 *	Once it finds it, it expands it.
 */
static char	search_environment_variables(t_token *token,
	t_list **environment_vars)
{
	char			*content;
	t_content_data	content_data;
	char			expanded;

	content_data.start = token->content;
	content_data.len = 0;
	content_data.single_q = 0;
	content_data.double_q = 0;
	content = token->content;
	expanded = NOT_EXPANDED;
	while (*content)
	{
		if (can_expand_env_var(content, &content_data))
		{
			expand_env_var(&content, &content_data, environment_vars);
			expanded = EXPANDED;
		}
		else
		{
			content++;
			content_data.len++;
		}
	}
	append_last_chars(*environment_vars, content_data);
	return (expanded);
}

/*
 *	Searches STR_TOKENs that may contain environmental variables.
 *	If the content of the token contained an environmental variable,
 *	it returns a t_list with the updated content.
 *	This new t_list must be inserted into tokens and must swap the token
 *	that was searched.
 */
static void	expand_environment_variables(t_list **tokens, t_list **new_tokens)
{
	t_list	*new_list;
	t_list	*node;
	t_token	*token;

	if (*tokens == NULL)
		return ;
	token = (t_token *)((*tokens)->content);
	if (token->type == STR_TOKEN && token->content != NULL)
	{
		new_list = NULL;
		if (search_environment_variables(token, &new_list) == EXPANDED)
		{
			ft_lstadd_back(new_tokens, new_list);
			node = *tokens;
			*tokens = (*tokens)->next;
			node->next = NULL;
			ft_lstdelone(node, del_token);
			expand_environment_variables(tokens, new_tokens);
			return ;
		}
	}
	node = *tokens;
	*tokens = (*tokens)->next;
	node->next = NULL;
	ft_lstadd_back(new_tokens, node);
	expand_environment_variables(tokens, new_tokens);
}

/*
 * 	First it expands the environment variables and then
 *	it expands the wildcards (environment variables can have * inside of them)
 */
void	expansor(t_list **tokens)
{
	t_list	*new_tokens;

	new_tokens = NULL;
	expand_environment_variables(tokens, &new_tokens);
	*tokens = new_tokens;
	//expand_wildcards(tokens);
}
