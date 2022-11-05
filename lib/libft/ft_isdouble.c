/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 09:18:13 by rokupin           #+#    #+#             */
/*   Updated: 2022/11/05 12:23:17 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_doubledot(char *val)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (val[i])
	{
		if (val[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		return (1);
	return (0);
}

int	ft_isdouble(char *val)
{
	int	i;

	i = 0;
	if (check_doubledot(val))
		return (0);
	if (val[i] == '-')
	{
		i++;
		if (!val[i])
			return (0);
	}
	while (val[i])
	{
		if (((val[i] < '0' || val[i] > '9') && val[i] != '.')
			|| ((val[i] == '.' && (
						i == 0
						|| !(val[i + 1])
						|| val[i - 1] == '-'))))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
