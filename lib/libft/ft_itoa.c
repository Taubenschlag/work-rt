/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:15:06 by rokupin           #+#    #+#             */
/*   Updated: 2020/01/22 12:04:44 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(long long n)
{
	long	fix;
	int		negative;
	int		range;
	char	*a;

	negative = (n < 0) ? 1 : 0;
	n = (negative) ? n * -1 : n;
	fix = n;
	range = get_range(n, negative);
	a = malloc(sizeof(char) * (range + 1));
	if (!a)
		return (NULL);
	a[range--] = '\0';
	if (negative && range--)
		a[0] = '-';
	while (range >= 0)
	{
		a[range + negative] = (fix % 10) + '0';
		fix /= 10;
		range--;
	}
	return (a);
}
