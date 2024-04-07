/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:15:27 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:15:38 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_err(int fd, char *str, int *err)
{
	int	count;

	count = ft_putstr_err(fd, str, err);
	if (!*err)
		count += ft_putchar_err(fd, '\n', err);
	return (count);
}
