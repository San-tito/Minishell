/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:35:50 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/19 17:16:22 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static int	heredoc_write(int fd, char *heredoc)
{
	size_t	nw;
	int		e;
	size_t	herelen;

	errno = 0;
	herelen = ft_strlen(heredoc);
	nw = write(fd, heredoc, herelen);
	e = errno;
	if (nw != herelen)
	{
		if (e == 0)
			e = ENOSPC;
		return (e);
	}
	return (0);
}

static int	here_document_to_fd(char *redirectee)
{
	int	r;
	int	herepipe[2];

	if (pipe(herepipe) < 0)
		return (-1);
	r = heredoc_write(herepipe[1], redirectee);
	if (r)
	{
		close(herepipe[0]);
		return (-1);
	}
	close(herepipe[1]);
	return (herepipe[0]);
}

static int	do_redirection(t_redirect *redirect)
{
	int					fd;
	enum e_instruction	ri;

	ri = redirect->instruction;
	if (ri == r_reading_until)
		fd = here_document_to_fd(redirect->filename);
	else
		fd = open(redirect->filename, redirect->flags, 0666);
	if (fd < 0)
		return (errno);
	if ((fd != redirect->dest) && (dup2(fd, redirect->dest) < 0))
	{
		close(fd);
		return (errno);
	}
	if (fd != redirect->dest)
		close(fd);
	return (0);
}

int	do_redirections(t_redirect *list)
{
	t_redirect	*temp;
	int			error;

	temp = list;
	while (temp)
	{
		error = do_redirection(temp);
		if (error)
		{
			internal_error("%s: %s", temp->filename, strerror(error));
			return (error);
		}
		temp = temp->next;
	}
	return (0);
}
