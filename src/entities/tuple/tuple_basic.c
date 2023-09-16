/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 10:22:29 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	tuple_vector(t_tuple *t, double x, double y, double z)
{
	//t_tuple	*t;

	//t = (t_tuple *)malloc(sizeof(t_tuple));
	t->x = x;
	t->y = y;
	t->z = z;
	t->type = IS_VECTOR;
	//return (t);
}

void	tuple_point(t_tuple *t, double x, double y, double z)
{
	//t_tuple	*t;

	//t = (t_tuple *)malloc(sizeof(t_tuple));
	t->x = x;
	t->y = y;
	t->z = z;
	t->type = IS_POINT;
	//return (t);
}

/*
t_tuple	*tuple_vector(double x, double y, double z)
{
	t_tuple	*t;

	t = (t_tuple *)malloc(sizeof(t_tuple));
	t->x = x;
	t->y = y;
	t->z = z;
	t->type = IS_VECTOR;
	return (t);
}

t_tuple	*tuple_point(double x, double y, double z)
{
	t_tuple	*t;

	t = (t_tuple *)malloc(sizeof(t_tuple));
	t->x = x;
	t->y = y;
	t->z = z;
	t->type = IS_POINT;
	return (t);
}

void	tuple_free(t_tuple *tuple)
{
	free(tuple);
}
*/
int	check_parsed_tuple(char **val)
{
	int	i;
	int	j;
	int	ret;

	ret = 1;
	i = -1;
	while (val[++i])
	{
		j = 0;
		if (val[i][j] == '-')
			j++;
		while (val[i][j])
		{
			if (((val[i][j] < '0' || val[i][j] > '9') && val[i][j] != '.')
				|| ((val[i][j] == '.' && (j == 0 || !(val[i][j + 1])))))
			{
				ret = 0;
				break ;
			}
			j++;
		}
	}
	if (i != 3)
		ret = 0;
	return (ret);
}

int	is_tuple(char *value, int exclude_neg)
{
	char	**next_part;
	int		ret;
	int		i;
	int		dot;

	i = 0;
	dot = 0;
	while (value[i])
	{
		if (value[i] == '.')
			dot++;
		if (value[i] == ',' && dot == 1)
			dot = 0;
		if ((value[i] == '-' && exclude_neg) || dot > 1)
			return (0);
		i++;
	}
	next_part = ft_split(value, ',');
	ret = check_parsed_tuple(next_part);
	i = -1;
	while (next_part[++i])
		free(next_part[i]);
	free(next_part);
	return (ret);
}
