/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:11:27 by rokupin           #+#    #+#             */
/*   Updated: 2019/10/16 11:03:18 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_num(const char *num, int negative)
{
	long    atoi;
    int     i;

    i = 0;
	atoi = 0;
	while ((num[i]) && (num[i] >= '0' && num[i] <= '9'))
	{
		atoi *= 10;
		atoi += num[i] - '0';
		i++;
		if (negative == -1 && atoi > 2147483648)
			return (0);
		else if (negative == 1 && atoi > 2147483647)
			return (-1);
	}
	return ((int)atoi * negative);
}

int			ft_atoi(const char *str)
{
	int		negative;
	char	*ptr;

	ptr = (char *)str;
	negative = 0;
	while (*ptr && ((*ptr >= 9 && *ptr <= 13) || *ptr == ' '))
		ptr++;
	if (*ptr && (*ptr == '-' || *ptr == '+'))
	{
		if (*ptr == '-')
			negative++;
		ptr++;
	}
	if (negative > 0)
		negative = -1;
	else
		negative = 1;
	return (handle_num(ptr, negative));
}
