/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:01:05 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:01:25 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cleanup(const char *str, char *n, char c)
{
	while (*str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	*n = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*n *= -1;
		str++;
	}
	while (*str == c)
		str++;
	return ((char *)str);
}

int	ft_atoi_err(const char *str, char *err)
{
	unsigned int	num;
	unsigned int	min;
	char			n;

	str = cleanup(str, &n, '0');
	num = 0;
	min = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		if (num > min)
			min = num;
		else
		{
			*err = 1;
			return (0);
		}
		str++;
	}
	if ((num - 1 > MAX_INT && n == -1) || (num > MAX_INT) || *str != '\0')
		*err = 1;
	return (num * n);
}

int	ft_atoi(const char *str)
{
	int		num;
	char	n;

	str = cleanup(str, &n, '0');
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	num *= n;
	return (num);
}

static int	get_pos_base(char c, char *base)
{
	int	pos;

	pos = 0;
	while (base[pos] != '\0')
	{
		if (base[pos] == c)
			return (pos);
		pos++;
	}
	return (0);
}

int	ft_atoi_base(const char *str, char *base)
{
	int		num;
	char	n;
	int		len;

	if (base == NULL)
		return (0);
	str = cleanup(str, &n, base[0]);
	num = 0;
	len = ft_strlen(base);
	while (ft_strchr(base, *str) && *str != '\0')
	{
		num = num * len + get_pos_base(*str, base);
		str++;
	}
	num *= n;
	return (num);
}
