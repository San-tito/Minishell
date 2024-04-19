/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

static void clear_simple_command(t_simple_com *command)
{
    //clear words
    //clear redirects
    free(command);
}

static void clear_connection(t_connection *connection)
{
    clear_command(&(connection->first));
    clear_command(&(connection->second));
    free(connection);
}

//static void clear_subshell(){}

void	clear_command(t_command **command)
{
	t_command_type	type;

	type = (*command)->type;
	if (type == cm_simple)
		clear_simple_command((t_simple_com *)((*command)->value));
	else if (type == cm_connection)
		clear_connection((t_connection *)((*command)->value));
	else
        ft_printf(1, "clear_subshell.\n");
		//clear_subshell((t_simple_com *)((*command)->value));
    free(*command);
}
