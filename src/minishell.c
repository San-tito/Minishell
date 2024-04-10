/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/10 15:53:29 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_initialize(void)
{
	/* Initialize various components like signals, builtins, jobs */
}

int	main(void)
{
	shell_initialize();
	reader_loop();
	exit_shell(g_last_exit_value);
}

void	exit_shell(int s)
{
	/* Clean up */
	exit(s);
}
