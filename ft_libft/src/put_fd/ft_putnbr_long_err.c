/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long_err.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:16:13 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:16:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_long_err(int fd, unsigned long number, char *base, int *err)
{
	int	count;

	if (number / ft_strlen(base) < 1)
		return (ft_putchar_err(fd, base[number], err));
	else
	{
		count = ft_putnbr_long_err(fd, number / ft_strlen(base), base, err);
		if (!*err)
			count += ft_putchar_err(fd, base[number % ft_strlen(base)], err);
		return (count);
	}
}
