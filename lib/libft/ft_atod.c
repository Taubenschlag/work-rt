/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:21:13 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/22 09:29:12 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(char *str)
{
	int		f;
	double	s;
	int		div;
	double	res;
	int		negative;

	f = ft_atoi(str);
	if (f < 0)
		f = f * -1;
	negative = str[0] == '-';
	div = get_range((long)f, negative);
	str += sizeof(char) * (div);
	if (*str == '.')
		str += sizeof(char);
	s = (double)ft_atoi(str);
	div = ft_strlen(str);
	while (--div >= 0)
		s /= 10;
	res = (double)(s + f);
	if (negative)
		res *= -1;
	return (res);
}
