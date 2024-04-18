/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/18 18:58:50 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
