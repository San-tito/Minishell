/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:44:52 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/21 19:56:15 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_variables(char **env, size_t count)
{
	size_t	i;
	size_t	j;
	char	*var1;
	char	*var2;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			var1 = env[j];
			var2 = env[j + 1];
			while (*var1 && *var1 != '=' && *var2 && *var2 != '='
				&& *var1 == *var2)
			{
				var1++;
				var2++;
			}
			if (*var1 > *var2)
				swap(env + j, env + j + 1);
			j++;
		}
		i++;
	}
}

int	show_variable_list(void)
{
	char	**copy;
	size_t	count;
	size_t	i;

	count = 0;
	while (environ[count])
		count++;
	copy = sh_malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		copy[i] = sh_strdup(environ[i]);
		i++;
	}
	copy[count] = NULL;
	sort_variables(copy, count);
	i = 0;
	while (i < count && (*copy[i] == '_') == 0)
		ft_printf("declare -%s %s\n", "x", copy[i++]);
	sh_doublefree((void **)copy);
	return (0);
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
