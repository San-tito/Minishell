/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:42:47 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 17:42:35 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_varlist	*vlist_realloc(t_varlist *vlist, int n)
{
	if (vlist == 0)
		return (vlist = vlist_alloc(n));
	if (n > vlist->list_size)
	{
		vlist->list_size = n;
		vlist->list = sh_realloc(vlist->list, (vlist->list_size + 1)
				* sizeof(t_variable *));
	}
	return (vlist);
}

void	vlist_add(t_varlist *vlist, t_variable *var)
{
	int	i;

	i = 0;
	while (i < vlist->list_len)
	{
		if (ft_strncmp(var->name, vlist->list[i]->name, ft_strlen(var->name)
				+ 1) == 0 && vlist->list[i]->name[ft_strlen(var->name)] == '\0')
			break ;
		i++;
	}
	if (i < vlist->list_len)
		return ;
	if (i >= vlist->list_size)
		vlist = vlist_realloc(vlist, vlist->list_size + 16);
	vlist->list[vlist->list_len++] = var;
	vlist->list[vlist->list_len] = NULL;
}

t_varlist	*varlist(void)
{
	static t_varlist	*vlist;

	if (vlist == 0)
		return (vlist = vlist_alloc(32));
	return (vlist);
}

t_varlist	*vlist_alloc(int nentries)
{
	t_varlist	*vlist;

	vlist = sh_malloc(sizeof(t_varlist));
	vlist->list = sh_malloc((nentries + 1) * sizeof(t_variable *));
	vlist->list_size = nentries;
	vlist->list_len = 0;
	vlist->list[0] = NULL;
	return (vlist);
}
