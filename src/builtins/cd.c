/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:49 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/13 16:50:58 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setpwd(void)
{
	char	*pwdvar;
	char	*dirname;

	pwdvar = getenv("PWD");
	update_env("OLDPWD=", pwdvar);
	dirname = getcwd(0, 0);
	update_env("PWD=", dirname);
	return (EXECUTION_SUCCESS);
}

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
			return (internal_error("%s: %s", __func__, "HOME not set"),
				EXECUTION_FAILURE);
	}
	else if (*list->word == '-' && *(list->word + 1) == '\0')
	{
		dirname = getenv("OLDPWD");
		if (dirname == 0)
			return (internal_error("%s: %s", __func__, "OLDPWD not set"),
				EXECUTION_FAILURE);
	}
	else
		dirname = list->word;
	if (chdir(dirname) == 0)
		return (setpwd());
	internal_error("%s: %s: %s", __func__, dirname, strerror(errno));
	return (EXECUTION_FAILURE);
}
