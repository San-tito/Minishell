/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:20:05 by sguzman           #+#    #+#             */
/*   Updated: 2024/03/10 16:37:51 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser(char *job)
{
	t_list	*tokens;
	pid_t	pid;
	int		status;

	if (job == NULL || *jop == '\0')
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	else if (pid == 0)
	{
		tokens = NULL;
		lexer(job, &tokens);
		expansor(&tokens);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	if (status != 0)
		return (NULL);
	return (convert_tokens(&tokens));
}
