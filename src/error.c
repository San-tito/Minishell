/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:30 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/10 12:59:59 by sguzman          ###   ########.fr       */
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

	fprintf(stderr, "%s: ", ename);
	va_start(args, format);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
}

void	internal_warning(const char *format, ...)
{
	va_list		args;
	const char	*ename = PROGRAM;

	fprintf(stderr, "%s: ", ename);
	fprintf(stderr, "warning: ");
	va_start(args, format);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
}

void	sys_error(const char *format, ...)
{
	int			e;
	va_list		args;
	const char	*ename = PROGRAM;

	e = errno;
	fprintf(stderr, "%s: ", ename);
	va_start(args, format);
	vfprintf(stderr, format, args);
	fprintf(stderr, ": %s\n", strerror(e));
	va_end(args);
}

void	fatal_error(const char *format, ...)
{
	va_list		args;
	const char	*ename = PROGRAM;

	fprintf(stderr, "%s: ", ename);
	va_start(args, format);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(2);
}
