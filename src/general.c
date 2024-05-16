/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:37 by sguzman           #+#    #+#             */
/*   Updated: 2024/05/16 13:37:57 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(int c)
{
	return (c == 0x20 || c == 0xD || c == 0xA || c == 0x9);
}

int	legal_number(const char *string, size_t *result)
{
	int	value;

	if (result)
		*result = 0;
	if (string == 0)
		return (0);
	value = ft_atoi(string);
	while (ft_isspace(*string))
		string++;
	if (*string == '+' || *string == '-')
		string++;
	while (ft_isdigit(*string))
		string++;
	if (*string == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}
