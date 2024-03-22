/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:10:54 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/20 17:03:43 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reader_loop(void)
{
	int	last_command_exit_value;

	last_command_exit_value = 0;
	read_command();
	return (last_command_exit_value);
}

int	parse_command(void)
{
	int	r;

	r = 0;
	while (42)
		readline("> ");
	return (r);
}

int	read_command(void)
{
	int	result;

	result = parse_command();
	return (result);
}
