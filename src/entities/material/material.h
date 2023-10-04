/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:22:45 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "../../../heads_global/minirt.h"

typedef struct light			t_light;

typedef struct matrl
{
	int		pattern;
	t_tuple	color;
	double	diffuse;
	double	ambient;
	double	specular;
	double	shininess;
}	t_matrl;

typedef struct lightning_pack
{
	t_matrl	*m;
	t_light	*l;
	t_tuple	posit;
	t_tuple	eye_v;
	t_tuple	norm_v;
	t_tuple	ef_color;
	t_tuple	lightv;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	reflv;
	double	rf_dot_eye;
	double	light_dot_norm;
}	t_lightning_pack;

void	lightning(t_tuple *amb_color, t_lightning_pack *p, int in_shadow);
void	mat_with_col(t_matrl *res, t_tuple *color);

#endif
