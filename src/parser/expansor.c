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

static char	*obtain_word(char **str)
{
	t_word	word;

    (*str)++;
	word.start = *str;
	word.len = 0;
	while (**str != ' ' && **str != '\'' && **str != '\"' && **str)
	{
		(*str)++;
		word.len++;
	}
	return (ft_substr(word.start, 0, word.len));
}

static char	append_str(char **str, char **str_to_add)
{
	char	*word;

	if (*str == NULL)
		*str = *str_to_add;
	else
	{
		word = ft_strjoin(*str, *str_to_add);
		free(*str_to_add);
		free(*str);
		if (word == NULL)
			return (0);
		*str = word;
	}
	ft_printf("Word appended: %s\n", word);
	return (1);
}

static char	expand_value(char **str, char **new)
{
	char	*word;
	char	*env;

	word = obtain_word(str);
	if (word == NULL)
	{
		if (*new != NULL)
			free(*new);
		return (0);
	}
	env = getenv(word);
	free(word);
	if (env == NULL)
		return (1);
    word = ft_strdup(env);
    if (word == NULL)
    {
		if (*new != NULL)
			free(*new);
		return (0);
	}
	return (append_str(new, &word));
}

static char	copy_word(char **new, t_word word)
{
	char	*str;

	if (word.len == 0) //no word to copy
		return (1);
	str = ft_substr(word.start, 0, word.len);
	if (str == NULL)
	{
		if (*new != NULL)
			free(*new);
		return (0);
	}
	return (append_str(new, &str));
}

static char	manage_variable(t_token *token)
{
	char	*str;
	char	*new;
	t_word	word;

	str = token->content;
	word.start = str;
	word.len = 0;
    word.single_q = 0;
    word.double_q = 0;
	new = NULL;
	while (*str)
	{
        if (*str == '\'' && !word.double_q)
            word.single_q = !word.single_q;
        else if (*str == '\"' && !word.single_q)
            word.double_q = !word.double_q;
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '\0' && !word.single_q)
		{
			if (!copy_word(&new, word))
				return (0);
			word.len = 0;
			if (!expand_value(&str, &new))
				return (0);
			word.start = str;
		}
		else
		{
			str++;
			word.len++;
		}
	}
	if (!copy_word(&new, word))
		return (0);
	str = token->content;
	token->content = new;
	free(str);
	return (1);
}

char	expansor(t_list **tokens)
{
	t_list  *lst;
	t_token	*token;

	lst = *tokens;
	if (lst == NULL) //should never happen
		return (0);
	while (lst)
	{
		token = (t_token *)(lst->content);
		if (token->type == STR_TOKEN)
			if (!manage_variable(token))
				return (handle_token_error(tokens, MALLOC_ERROR));
		lst = lst->next;
	}
	return (1);
}
