/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:44:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/23 01:57:17 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_varlist(t_varlist *vlist)
{
	t_variable	*key;
	int			i;
	int			j;

	i = 0;
	while (i < vlist->list_len)
	{
		key = vlist->list[i];
		j = i - 1;
		while (j >= 0 && ft_strncmp(vlist->list[j]->name, key->name,
				ft_strlen(key->name) + 1) > 0)
		{
			vlist->list[j + 1] = vlist->list[j];
			j = j - 1;
		}
		vlist->list[j + 1] = key;
		i++;
	}
}

t_varlist	*copy_varlist(t_varlist *src)
{
	t_varlist	*dest;
	int			i;

	if (src == 0)
		return (0);
	dest = sh_malloc(sizeof(t_varlist));
	dest->list_len = src->list_len;
	dest->list = sh_malloc((src->list_len + 1) * sizeof(t_variable *));
	i = 0;
	while (i < src->list_len)
	{
		dest->list[i] = sh_malloc(sizeof(t_variable));
		dest->list[i]->name = sh_strdup(src->list[i]->name);
		dest->list[i]->value = sh_strdup(src->list[i]->value);
		dest->list[i]->attributes = src->list[i]->attributes;
		i++;
	}
	dest->list[src->list_len] = 0;
	return (dest);
}

void	show_variable_list(void)
{
	t_varlist	*original;
	t_varlist	*vlist;
	int			i;

	original = varlist();
	vlist = copy_varlist(original);
	sort_varlist(vlist);
	i = -1;
	while (++i < vlist->list_len)
	{
		if (*vlist->list[i]->name != '_')
		{
			ft_printf("declare -%c ", 'x');
			ft_printf("%s", vlist->list[i]->name);
			if (vlist->list[i]->attributes & ATT_EXPORT)
				ft_printf("=\"%s\"", vlist->list[i]->value);
			ft_printf("\n");
		}
	}
	vlist_clear(vlist);
}

static int	is_legal(char *name, int *append)
{
	int		i;
	int		len;
	char	*assign;

	if (!name || !*name || ft_isalpha(*name) == 0)
		return (0);
	len = ft_strlen(name);
	assign = ft_strchr(name, '=');
	if (assign)
	{
		len = assign - name;
		if (name[assign - name - 1] == '+')
		{
			len = assign - name - 1;
			*append = 1;
		}
	}
	i = 1;
	while (*(name + i) && i < len)
	{
		if ((ft_isalnum(*(name + i)) || *(name + i) == '_') == 0)
			return (0);
		i++;
	}
	return (1);
}

int	export_builtin(t_word_list *list)
{
	int		result;
	int		append;
	char	*name;

	append = 0;
	result = EXECUTION_SUCCESS;
	if (list)
	{
		while (list)
		{
			name = list->word;
			if (is_legal(name, &append) == 0)
			{
				internal_error("%s: `%s': not a valid identifier", "export",
					name);
				result = EXECUTION_FAILURE;
			}
			else
				add_exported(name, append);
			list = list->next;
		}
	}
	else
		show_variable_list();
	return (result);
}
