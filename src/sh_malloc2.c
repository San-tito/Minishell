/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_malloc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:09:36 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 13:23:45 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_exit(int s)
{
	rl_clear_history();
	vlist_clear(varlist());
	exit(s);
}

char	*sh_substr(const char *str, unsigned int start, size_t len)
{
	char	*substr;

	substr = ft_substr(str, start, len);
	if (substr == NULL)
		fatal_error("Not enough memory to substr %s", str);
	return (substr);
}

char	*sh_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (join == NULL)
		fatal_error("Not enough memory to join [%s] and [%s]", s1, s2);
	return (join);
}

t_list	*sh_lstnew(void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (node == NULL)
		fatal_error("Not enough memory create a new node");
	return (node);
}

char	*sh_itoa(int n)
{
	char	*itoa;

	itoa = ft_itoa(n);
	if (itoa == NULL)
		fatal_error("Not enough memory create itoa %d", n);
	return (itoa);
}
