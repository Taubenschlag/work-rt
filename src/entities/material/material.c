/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/29 19:49:41 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/**
 *	- Ambient reflection is background lighting, or light reflected from other
 *	objects in the environment. The Phong model treats this as a constant,
 *	coloring all points on the surface equally.
 *	- Diffuse reflection is light reflected from a matte surface. It depends
 *	only on the angle between the light source and the surface normal.
 *	- Specular reflection is the reflection of the light source itself and
 *	results in what is called a specular highlight—the bright spot on a
 *	curved surface. It depends only on the angle between the reflection vector
 *	and the eye vector and is controlled by a parameter that we’ll call
 *	shininess. The higher the shininess, the smaller and tighter the specular
 *	highlight
 */
void	mat_with_col(t_matrl *res, t_tuple *color)
{
	tuple_copy(&res->color, color);
	res->ambient = 0.1;
	res->diffuse = 0.9;
	res->shininess = 200;
	res->specular = 0.9;
}
