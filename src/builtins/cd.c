/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:49 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 16:56:35 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

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

int	cd_builtin(t_word_list *list)
{
	char	*dirname;

	if (list == 0)
	{
		dirname = getenv("HOME");
		if (dirname == 0)
			return (internal_error("%s: %s", "cd", "HOME not set"),
				EXECUTION_FAILURE);
	}
	else if (*list->word == '-' && *(list->word + 1) == '\0')
	{
		dirname = getenv("OLDPWD");
		if (dirname == 0)
			return (internal_error("%s: %s", "cd", "OLDPWD not set"),
				EXECUTION_FAILURE);
	}
	else
		dirname = list->word;
	if (chdir(dirname) == 0)
		return (setpwd());
	internal_error("%s: %s: %s", "cd", dirname, strerror(errno));
	return (EXECUTION_FAILURE);
}
