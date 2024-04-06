/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:51:58 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 16:33:17 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_command *command)
{
	int	result;

	result = *(int *)(void *)command;
	return (result);
}

static int	execute_disk_command(t_word_list *words, t_redirect *redirects,
		char *command_line, int pipe_in, pipe_out, async,
		struct fd_bitmap *fds_to_close, int cmdflags)
{
	const char	*pathname = words->word;
	const char	*command = search_for_command (pathname);
}
