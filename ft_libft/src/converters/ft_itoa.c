/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:11:45 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:11:48 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int				size;
	unsigned int	num;

	size = 1;
	if (n < 0)
	{
		num = n * -1;
		size++;
	}
	else if (n == 0)
	{
		num = n;
		size++;
	}
	else
		num = n;
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

static int	rec_store_number(char *str, unsigned int number, int pos)
{
	if (number / 10 < 1)
		*str = number + '0';
	else
	{
		pos = rec_store_number(str, number / 10, pos);
		*(str + pos) = (number % 10) + '0';
	}
	return (pos + 1);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				size;
	unsigned int	number;

	size = get_num_len(n);
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		*str = '-';
		number = n * -1;
		rec_store_number(str + 1, number, 0);
	}
	else
		rec_store_number(str, n, 0);
	*(str + size - 1) = '\0';
	return (str);
}
