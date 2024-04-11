/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:23:18 by sguzman           #+#    #+#             */
/*   Updated: 2024/04/11 16:45:20 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_func	*find_builtin(char *name)
{
	static t_builtin	builtins[] = {{"cd", cd}, {"echo", echo}};
	const int			num_builtins = 2;
	int					i;

	i = 0;
	while (i < num_builtins)
	{
		if (ft_strncmp(name, builtins[i].name,
				ft_strlen(builtins[i].name)) == 0)
			return (builtins[i].function);
		i++;
	}
	return (NULL);
}

int	execute_builtin(t_builtin_func *builtin, t_word_list *words,
		t_redirect *redirects)
{
	int	result;

	if (redirects && (do_redirections(redirects) != 0))
		return (EXECUTION_FAILURE);
	result = ((*builtin)(words->next));
	return (result);
}
