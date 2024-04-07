/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:18:30 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/06 16:21:03 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	internal_error(const char *format, ...)
{
	va_list		args;
	const char	*ename = "minishell";

	fprintf(stderr, "%s: ", ename);
	va_start(args, format);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
}
