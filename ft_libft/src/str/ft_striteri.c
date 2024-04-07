/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:12:52 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:12:59 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	count;

	if (s == NULL || f == NULL)
		return ;
	count = 0;
	while (*(s + count) != '\0')
	{
		(*f)(count, s + count);
		count++;
	}
}
