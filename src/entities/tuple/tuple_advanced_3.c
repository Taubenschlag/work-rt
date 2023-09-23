/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_advanced_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 14:29:11 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	tuple_multiply(t_tuple *res, t_tuple *t1, t_tuple *t2)
{
	res->x = t1->x * t2->x;
	res->y = t1->y * t2->y;
	res->z = t1->z * t2->z;
	res->type = t1->type * t2->type;
}

void	tuple_reflect(t_tuple *res, t_tuple *v_in, t_tuple *v_normal)
{
	t_tuple	tmp;
	double	dot_prod;

	dot_prod = tuple_dot_product(v_in, v_normal) * 2;
	tuple_scalar_multiply(&tmp, v_normal, dot_prod);
	tuple_substract(res, v_in, &tmp);
}

void	tuple_color(t_tuple *res, double r, double g, double b)
{
	res->x = r;
	res->y = g;
	res->z = b;
	res->type = 2;
}

void	tuple_copy(t_tuple *res, t_tuple *t)
{
	tuple_point(res, t->x, t->y, t->z);
	res->type = t->type;
}

void	set_tuple(t_tuple *tuple, char *value, char type)
{
	char	**input;

	input = ft_split(value, ',');
	tuple->x = ft_atod(input[0]);
	tuple->y = ft_atod(input[1]);
	tuple->z = ft_atod(input[2]);
	if (type == 'p')
		tuple->type = IS_POINT;
	if (type == 'v')
		tuple->type = IS_VECTOR;
	if (type == 'c')
		tuple->type = 2;
	cleanup(input);
}
