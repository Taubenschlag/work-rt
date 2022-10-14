/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/14 22:03:37 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H
# include "../../../heads_global/minirt.h"
# define IS_POINT    1
# define IS_VECTOR   0

typedef struct tuple
{
	double	x;
	double	y;
	double	z;
	int		type;
}	t_tuple;

int		is_tuple(char *value, int exclude_neg);

t_tuple	*tuple_vector(double x, double y, double z);
t_tuple	*tuple_point(double x, double y, double z);
t_tuple	*tuple_color(double r, double g, double b);

void	tuple_free(t_tuple *tuple);
int		cheaty_free(t_tuple *tuple);

int		tuple_is_vector(t_tuple *tuple);

int		tuple_equals(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_add(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_substract(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_scalar_multiply(t_tuple *t, double scale);
t_tuple	*tuple_negate(t_tuple *t);
double	tuple_length(t_tuple *t);
t_tuple	*tuple_normalize(t_tuple *t);
double	tuple_dot_product(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_cross_product(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_multiply(t_tuple *t1, t_tuple *t2);
t_tuple	*tuple_reflect(t_tuple *v_in, t_tuple *v_normal);
t_tuple	*tuple_copy(t_tuple *t);

#endif 