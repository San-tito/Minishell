/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:30 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/20 22:59:38 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

void	internal_error(const char *format, ...)
{
	va_list		args;
	const char	*ename = PROGRAM;

	ft_dprintf(STDERR_FILENO, "%s: ", ename);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	ft_dprintf(STDERR_FILENO, "\n");
	va_end(args);
}

void	internal_warning(const char *format, ...)
{
	va_list		args;
	const char	*ename = PROGRAM;

	ft_dprintf(STDERR_FILENO, "%s: ", ename);
	ft_dprintf(STDERR_FILENO, "warning: ");
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	ft_dprintf(STDERR_FILENO, "\n");
	va_end(args);
}

void	sys_error(const char *format, ...)
{
	int			e;
	va_list		args;
	const char	*ename = PROGRAM;

	e = errno;
	ft_dprintf(STDERR_FILENO, "%s: ", ename);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	ft_dprintf(STDERR_FILENO, ": %s\n", strerror(e));
	va_end(args);
}

void	fatal_error(const char *format, ...)
{
	va_list		args;
	const char	*ename = PROGRAM;

	ft_dprintf(STDERR_FILENO, "%s: ", ename);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	ft_dprintf(STDERR_FILENO, "\n");
	va_end(args);
	exit(2);
}
