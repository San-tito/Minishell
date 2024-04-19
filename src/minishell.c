/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 17:16:40 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"

static void	shell_initialize(void)
{
	initialize_shell_level();
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
