/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:49 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/23 02:30:39 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "variables.h"
#include <errno.h>
#include <string.h>

static int	bindpwd(void)
{
	char	*pwdvar;

	pwdvar = find_env("PWD");
	update_env("OLDPWD", pwdvar);
	set_pwd();
	return (EXECUTION_SUCCESS);
}

int	cd_builtin(t_word_list *list)
{
	char	*dirname;

	if (list == 0)
	{
		dirname = find_env("HOME");
		if (dirname == 0)
			return (internal_error("%s: %s", "cd", "HOME not set"),
				EXECUTION_FAILURE);
	}
	else if (*list->word == '-' && *(list->word + 1) == '\0')
	{
		dirname = find_env("OLDPWD");
		if (dirname == 0)
			return (internal_error("%s: %s", "cd", "OLDPWD not set"),
				EXECUTION_FAILURE);
	}
	else
		dirname = list->word;
	if (chdir(dirname) == 0)
		return (bindpwd());
	internal_error("%s: %s: %s", "cd", dirname, strerror(errno));
	return (EXECUTION_FAILURE);
}
