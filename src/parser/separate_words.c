/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "separate_words.h"

static void	init_word_data(t_list **words, t_word_data *word_data, char *job)
{
	*words = NULL;
	word_data->first = job;
	word_data->len = 0;
	word_data->single_q = 0;
	word_data->double_q = 0;
}

static void	create_word(t_list **words, t_word_data *word_data, char **job)
{
	char	*word;
	t_list	*node;

	word = ft_substr(word_data->first, 0, word_data->len);
	if (word == NULL)
		handle_error_word(words, MALLOC_ERROR);
	node = ft_lstnew(word);
	if (node == NULL)
	{
		free(word);
		handle_error_word(words, MALLOC_ERROR);
	}
	ft_lstadd_back(words, node);
	word_data->first = (*job + 1);
	word_data->len = 0;
}

static t_list	*check_word_errors(t_list **words, t_word_data word_data, char *job)
{
	if (word_data.single_q)
		handle_error_word(words, SINGLE_Q_ERROR);
	if (word_data.double_q)
		handle_error_word(words, DOUBLE_Q_ERROR);
	create_word(words, &word_data, &job);
	return (*words);
}

static char	managa_quotes(char c, t_word_data *word_data)
{
	if (word_data->single_q)
	{
		if (c == '\'')
			word_data->single_q = 0;
	}
	else if (word_data->double_q)
	{
		if (c == '\"')
			word_data->double_q = 0;
	}
	else if (c == '\'')
		word_data->single_q = 1;
	else if (c == '\"')
		word_data->double_q = 1;
	else if (c == ' ')
		return (0);
	return (1);
}

t_list	*separate_words(char *job)
{
	t_word_data	word_data;
	t_list		*words;

	init_word_data(&words, &word_data, job);
	while (*job)
	{
		if (!managa_quotes(*job, &word_data))
			create_word(&words, &word_data, &job);
		else
			word_data.len++;
		job++;
	}
	return (check_word_errors(&words, word_data, job));
}
