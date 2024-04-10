/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:29:33 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/10 18:09:38 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reader_loop(void)
{
	char		*line;
	t_command	*current_command;

	current_command = NULL;
	while (42)
	{
		line = read_command();
		current_command = parse_command(line);
		execute_command(current_command);
	}
	return (g_last_exit_value);
}

char	*read_command(void)
{
	char	*line;
	char	prompt[80];

	ft_strlcpy(prompt, "\n" CYAN "Minishell " RESET "\n", sizeof(prompt));
	if (g_last_exit_value == 0)
		ft_strlcat(prompt, GREEN "❯ " RESET, sizeof(prompt));
	else
		ft_strlcat(prompt, RED "❯ " RESET, sizeof(prompt));
	line = readline(prompt);
	return (line);
}
