/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:35:50 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/07 19:03:13 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_redirection_internal(t_redirect *redirect)
{
	int					fd;
	enum e_instruction	ri;

	ri = redirect->instruction;
	if (ri != r_reading_until)
	{
		fd = open(redirect->filename, redirect->flags, 0666);
		if (fd < 0)
			return (errno);
	}
	return (0);
}

int	do_redirections(t_redirect *list)
{
	t_redirect	*temp;
	int			error;

	temp = list;
	while (temp)
	{
		error = do_redirection_internal(temp);
		if (error)
		{
			internal_error("%s: %s", temp->filename, strerror(error));
			return (error);
		}
		temp = temp->next;
	}
	return (0);
}
