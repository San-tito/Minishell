/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:37 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/23 14:23:34 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>

void	whitespaces(char **str)
{
	if (str == 0 || *str == 0)
		return ;
	while (**str == 0x20 || **str == 0xD || **str == 0xA || **str == 0x9)
		(*str)++;
}

static ssize_t	ft_strtoi(const char *nptr, char **endptr)
{
	ssize_t		acc;
	int			neg;
	const char	*s = nptr;

	acc = 0;
	whitespaces((char **)&s);
	neg = (*s == '-');
	if (*s == '-' || *s == '+')
		s++;
	if (ft_isdigit(*s) == 0 && endptr != 0)
		return (*endptr = (char *)nptr, acc);
	while (ft_isdigit(*s))
	{
		if (neg && (acc < (INTMAX_MIN + (*s - '0')) / 10))
			return (errno = ERANGE, acc = INTMAX_MIN);
		if (neg == 0 && (acc > (INTMAX_MAX - (*s - '0')) / 10))
			return (errno = ERANGE, acc = INTMAX_MAX);
		if (neg)
			acc = acc * 10 - (*s++ - '0');
		else
			acc = acc * 10 + (*s++ - '0');
	}
	if (endptr != 0)
		*endptr = (char *)s;
	return (acc);
}

int	legal_number(const char *string, ssize_t *result)
{
	ssize_t	value;
	char	*ep;

	if (result)
		*result = 0;
	if (string == 0)
		return (0);
	errno = 0;
	value = ft_strtoi(string, &ep);
	if (errno || ep == string)
		return (0);
	whitespaces(&ep);
	if (*string && *ep == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}

int	legal_identifier(char *name)
{
	char	*s;

	if (!name || !*name || (ft_isalpha(*name) || (*name == '_')) == 0)
		return (0);
	s = name + 1;
	while (*s)
	{
		if ((ft_isalnum(*s) || *s == '_') == 0)
			return (0);
		s++;
	}
	return (1);
}

void	int_to_buf(int number, char buffer[5])
{
	int	old_number;

	if (number < 0 || number > 9999)
		return ;
	if (number < 10)
	{
		buffer[0] = number + '0';
		buffer[1] = '\0';
	}
	else if (number < 100)
	{
		buffer[0] = (number / 10) + '0';
		buffer[1] = (number % 10) + '0';
		buffer[2] = '\0';
	}
	else if (number < 1000)
	{
		buffer[0] = (number / 100) + '0';
		old_number = number % 100;
		buffer[1] = (old_number / 10) + '0';
		buffer[2] = (old_number % 10) + '0';
		buffer[3] = '\0';
	}
}
