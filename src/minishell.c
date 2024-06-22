/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 16:52:44 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"
#include "sig.h"

static void	shell_initialize(char **env)
{
	initialize_shell_variables(env);
	default_signals();
	set_pwd();
	initialize_shell_level();
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)&(argc);
	(void)&(argv);
	shell_initialize(envp);
	reader_loop();
	sh_exit(g_last_exit_value);
}

void	sh_exit(int s)
{
	exit(s);
}
