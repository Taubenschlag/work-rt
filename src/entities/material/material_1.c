/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/16 23:10:30 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	make_l_p(t_lightning_pack *pack, t_light *l, t_computations *c)
{
	t_tuple	tmp;

	tuple_copy(&pack->eye_v, &c->eyev);
	pack->l = l;
	pack->m = c->shape->matrl;
	tuple_copy(&pack->norm_v, &c->normv);
	tuple_copy(&pack->posit, &c->point);
	tuple_multiply(&pack->ef_color, &c->shape->matrl->color, &l->color);
	tuple_substract(&tmp, &l->position, &c->point);
	tuple_normalize(&pack->lightv, &tmp);
	pack->light_dot_norm = tuple_dot_product(&pack->lightv, &pack->norm_v);
	if (pack->light_dot_norm < 0)
	 	tuple_color(&pack->diffuse, 0, 0, 0);
	else
	{
		tuple_scalar_multiply(&tmp, &pack->ef_color, pack->m->diffuse);
		tuple_scalar_multiply(&pack->diffuse, &tmp, pack->light_dot_norm);
	}
}

void	lightning(t_tuple *amb_color, t_lightning_pack *p, int in_shadow)
{
	t_tuple	tmp;
	double	pow_tmp;

	tuple_scalar_multiply(amb_color, &p->ef_color, p->m->ambient);
	if (p->light_dot_norm < 0)
		tuple_color(&p->specular, 0, 0, 0);
	else
	{
		tuple_negate(&tmp, &p->lightv);
		tuple_reflect(&p->reflv, &tmp, &p->norm_v);
		p->rf_dot_eye = tuple_dot_product(&p->reflv, &p->eye_v);
		if (p->rf_dot_eye <= 0)
			tuple_color(&p->specular, 0, 0, 0);
		else
		{
			tuple_scalar_multiply(&tmp, &p->l->color, p->m->specular);
			pow_tmp = pow(p->rf_dot_eye, p->m->shininess);
			tuple_scalar_multiply(&p->specular, &tmp, pow_tmp);
		}
						
	}
	if (!in_shadow)
	{
		tuple_add(&tmp, amb_color, &p->diffuse);
		tuple_add(amb_color, &tmp, &p->specular);
	}
	//cleanup_light_pack(p);
}

/*
t_lightning_pack	*make_l_p(t_light *l, t_computations *c)
{
	t_lightning_pack	*pack;

	pack = (t_lightning_pack *)malloc(sizeof(t_lightning_pack));
	pack->eye_v = c->eyev;
	pack->l = l;
	pack->m = c->shape->matrl;
	pack->norm_v = c->normv;
	pack->posit = c->point;
	pack->ef_color = tuple_multiply(c->shape->matrl->color, l->color);
	pack->lightv = tuple_normalize(
			tuple_substract(tuple_copy(l->position), tuple_copy(c->point)));
	pack->light_dot_norm = tuple_dot_product(pack->lightv, pack->norm_v);
	if (pack->light_dot_norm < 0)
		pack->diffuse = tuple_color(0, 0, 0);
	else
	{
		pack->diffuse = tuple_scalar_multiply(
				tuple_scalar_multiply(tuple_copy(pack->ef_color),
					pack->m->diffuse), pack->light_dot_norm);
	}
	return (pack);
}

t_tuple	*lightning(t_lightning_pack *p, int in_shadow)
{
	t_tuple	*amb_color;

	amb_color = tuple_scalar_multiply(tuple_copy(p->ef_color), p->m->ambient);
	if (p->light_dot_norm < 0)
		p->specular = tuple_color(0, 0, 0);
	else
	{
		p->reflv = tuple_reflect(tuple_negate(tuple_copy(p->lightv)),
				p->norm_v);
		p->rf_dot_eye = tuple_dot_product(p->reflv, p->eye_v);
		free(p->reflv);
		if (p->rf_dot_eye <= 0)
			p->specular = tuple_color(0, 0, 0);
		else
			p->specular = tuple_scalar_multiply(
					tuple_scalar_multiply(tuple_copy(p->l->color),
						p->m->specular), pow(p->rf_dot_eye, p->m->shininess));
	}
	if (!in_shadow)
		amb_color = tuple_add(
				tuple_add(amb_color, tuple_copy(p->diffuse)), p->specular);
	else
		tuple_free(p->specular);
	cleanup_light_pack(p);
	return (amb_color);
}

void	cleanup_light_pack(t_lightning_pack *l)
{
	free(l->posit);
	free(l->eye_v);
	free(l->norm_v);
	free(l->ef_color);
	free(l->diffuse);
	free(l->lightv);
	free(l);
}
*/