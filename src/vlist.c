/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:42:47 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/22 22:45:15 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_varlist	*vlist_realloc(t_varlist *vlist, int n)
{
	int			i;
	t_variable	**new_list;

	new_list = sh_malloc((n + 1) * sizeof(t_variable *));
	i = 0;
	while (i < vlist->list_len)
	{
		new_list[i] = vlist->list[i];
		i++;
	}
	new_list[vlist->list_len] = NULL;
	free(vlist->list);
	vlist->list = new_list;
	vlist->list_size = n;
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
		return (clear_variable(var));
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

void	vlist_clear(t_varlist *vlist)
{
	int	i;

	if (vlist == 0)
		return ;
	i = 0;
	while (i < vlist->list_len)
	{
		clear_variable(vlist->list[i]);
		i++;
	}
	sh_free(vlist->list);
	sh_free(vlist);
}
