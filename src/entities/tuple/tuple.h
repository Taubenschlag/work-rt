/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 14:32:11 by sbocanci         ###   ########.fr       */
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

void	tuple_set(t_tuple *t, double x, double y, double z);
void	tuple_vector(t_tuple *t, double x, double y, double z);
void	tuple_point(t_tuple *t, double x, double y, double z);
void	tuple_color(t_tuple *res, double r, double g, double b);
int		is_tuple(char *value, int exclude_neg);

/* tuple_advanced_1.c */
int		tuple_is_vector(t_tuple *tuple);
int		tuple_equals(t_tuple *t1, t_tuple *t2);
void	tuple_add(t_tuple *res, t_tuple *t1, t_tuple *t2);
void	tuple_substract(t_tuple *res, t_tuple *t1, t_tuple *t2);
void	tuple_scalar_multiply(t_tuple *res, t_tuple *t, double scale);

/* tuple_advanced_2.c */
void	tuple_negate(t_tuple *res, t_tuple *t);
double	tuple_length(t_tuple *t);
void	tuple_normalize(t_tuple *res, t_tuple *t);
double	tuple_dot_product(t_tuple *t1, t_tuple *t2);
void	tuple_cross_product(t_tuple *res, t_tuple *t1, t_tuple *t2);

/* tuple_advanced_3.c */
void	tuple_multiply(t_tuple *res, t_tuple *t1, t_tuple *t2);
void	tuple_reflect(t_tuple *res, t_tuple *v_in, t_tuple *v_normal);
void	tuple_color(t_tuple *res, double r, double g, double b);
void	tuple_copy(t_tuple *res, t_tuple *t);
void	set_tuple(t_tuple *tuple, char *value, char type);

#endif 