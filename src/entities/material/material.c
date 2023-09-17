/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 22:20:30 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

/* DEBUG */
void	print_material(t_matrl *m)
{
	printf("\t\t========================\n");
	printf("\t\tMATERIAL\n");
	printf("\t\tcolor: ");
	print_tuple(&m->color);
	printf("\t\tdiffuse:[%.2f], amb:[%.2f], spec:[%.2f], shin:[%.2f]\n", m->diffuse, m->ambient, m->specular, m->shininess);
	printf("\t\t= = = = = = = = = = = = =\n");
}
/* ***** */

void	mat_with_col(t_matrl *res, t_tuple *color)
{
	tuple_copy(&res->color, color);
	res->ambient = 0.1;
	res->diffuse = 0.9;
	res->shininess = 200;
	res->specular = 0.9;
}