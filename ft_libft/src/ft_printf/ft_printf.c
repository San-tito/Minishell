/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:50 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	choose_conversion(int fd, char const *str, va_list va, int *err)
{
	int	count;

	count = 0;
	if (*str == 'c')
		count = ft_putchar_err(fd, va_arg(va, int), err);
	else if (*str == 's')
		count = ft_putstr_err(fd, va_arg(va, char *), err);
	else if (*str == 'u')
		count = ft_putunsnbr_err(fd, va_arg(va, int), DECBASE, err);
	else if (*str == 'p')
		count = ft_putptr_err(fd, va_arg(va, void *), err);
	else if (*str == 'i' || *str == 'd')
		count = ft_putnbr_err(fd, va_arg(va, int), DECBASE, err);
	else if (*str == 'x')
		count = ft_putunsnbr_err(fd, va_arg(va, int), HEXLOWBASE, err);
	else if (*str == 'X')
		count = ft_putunsnbr_err(fd, va_arg(va, int), HEXHIGHBASE, err);
	else if (*str == '%')
		count = ft_putchar_err(fd, '%', err);
	else
		*err = -1;
	return (count);
}

static int	print_output(int fd, char const *str, va_list va, int *err)
{
	int	count;

	count = 0;
	while (!*err && *str != '\0')
	{
		if (*str == '%')
		{
			str++;
			count += choose_conversion(fd, str, va, err);
		}
		else
			count += ft_putchar_err(fd, *str, err);
		str++;
	}
	if (*err)
		return (-1);
	return (count);
}

int	ft_printf(int fd, char const *str, ...)
{
	int			err;
	int			count;
	va_list		va;

	if (str == NULL)
		return (-1);
	err = 0;
	va_start(va, str);
	count = print_output(fd, str, va, &err);
	va_end(va);
	if (err)
		return (-1);
	return (count);
}
