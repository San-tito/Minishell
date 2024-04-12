/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:49 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/12 11:30:38 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	absolute_pathname(const char *string)
{
	if (string == 0 || *string == '\0')
		return (0);
	if (*string == '/')
		return (1);
	if (*string == '.' && (ft_strchr("/\\", *(string + 1)) || *(string
				+ 1) == 0))
		return (1);
	if (*string == '.' && *(string + 1) == '.' && (ft_strchr("/\\", *(string
					+ 2)) || *(string + 2) == 0))
		return (1);
	return (0);
}

int	cd(t_word_list *list)
{
	char	*dirname;

	if (list == 0)
	{
		dirname = getenv("HOME");
		if (dirname == 0)
		{
			internal_error("%s: %s", __func__, "HOME not set");
			return (EXECUTION_FAILURE);
		}
	}
	else if (*list->word == '-' && *(list->word + 1) == '\0')
	{
		dirname = getenv("OLDPWD");
		if (dirname == 0)
		{
			internal_error("%s: %s", __func__, "OLDPWD not set");
			return (EXECUTION_FAILURE);
		}
	}
	else if (absolute_pathname(list->word))
		dirname = list->word;
	return (EXECUTION_FAILURE);
}
