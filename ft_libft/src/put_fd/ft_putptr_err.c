/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:50 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_err(int fd, void *ptr, int *err)
{
	unsigned long	addr;

	ft_putstr_err(fd, "0x", err);
	if (!*err)
	{
		addr = (unsigned long)ptr;
		return (ft_putnbr_long_err(fd, addr, HEXLOWBASE, err) + 2);
	}
	return (0);
}
