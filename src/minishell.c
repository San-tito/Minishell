/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/20 16:41:40 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	const int	shell_terminal = STDIN_FILENO;
	const int	shell_is_interactive = isatty(shell_terminal);

	if (shell_is_interactive)
	{
		printf("interactive_shell");
	}
	reader_loop();
	exit_shell(EXIT_SUCCESS);
}

void	exit_shell(int s)
{
	/* Clean up */
	exit(s);
}
