/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 00:19:29 by rokupin           #+#    #+#             */
/*   Updated: 2020/01/22 11:03:00 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		check_base(char *base, int *base_set)
{
	int base_value;
	int i;

	i = 0;
	while (i < 94)
		base_set[i++] = 0;
	base_value = 0;
	while (base[base_value])
	{
		if (base[base_value] <= 32 ||
			base[base_value] > 126 ||
			base[base_value] == '+' ||
			base[base_value] == '-')
			return (0);
		base_set[base[base_value] - 32]++;
		base_value++;
	}
	if (base_value < 2)
		return (0);
	i = 0;
	while (i < 94)
		if (base_set[i++] > 1)
			return (0);
	return (base_value);
}

int		val(char *str, char c)
{
	int p;

	p = 0;
	while (str[p] && str[p] != c)
		p++;
	return (p);
}

int		negative(char **nbr)
{
	int		negative;

	negative = 0;
	while (nbr[0][0] && (nbr[0][0] == '-' || nbr[0][0] == '+'))
	{
		if (nbr[0][0] == '-')
			negative++;
		nbr[0]++;
	}
	if (negative % 2 == 1)
		negative = -1;
	else
		negative = 1;
	return (negative);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long	atoi;
	int		base_input_val;
	int		base_output_val;
	int		base_input_set[94];
	int		b_o_s[94];

	if (!(base_input_val = check_base(base_from, base_input_set)) ||
		!(base_output_val = check_base(base_to, b_o_s)))
		return (NULL);
	while (*nbr && *nbr <= ' ')
		nbr++;
	b_o_s[0] = negative(&nbr);
	atoi = 0;
	while (*nbr && base_input_set[*nbr - 32])
	{
		atoi *= base_input_val;
		atoi += val(base_from, *nbr);
		nbr++;
	}
	return (dec_to_any(atoi * b_o_s[0], base_to, base_output_val));
}
