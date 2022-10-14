/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/09/30 22:38:37 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../../../heads_global/minirt.h"
# define COLOR_CF 0.003921569 //WHY?

typedef struct scene
{
	int			resolution_x;
	int			resolution_y;
	double		ambi_ratio;
	t_tuple		*ambi_color;
	int			camera_counter;
	t_camera	**cameras;
	int			light_counter;
	t_light		**lights;
	int			shape_counter;
	t_shape		**shapes;
}	t_scene;

t_tuple		*get_tuple(char *value, char type);
void		free_scene(t_scene *s);
int			handle_r(char *line, t_scene *s);
int			handle_a(char *line, t_scene *s);
int			handle_c(char *line, t_scene *s, char *name);
int			handle_l(char *line, t_scene *s);
int			handle_shape(char *line, t_scene *s);
int			handle_plane(char **values, t_scene *s);
int			handle_sphere(char **values, t_scene *s);
int			handle_square(char **values, t_scene *s);
int			handle_cylinder(char **values, t_scene *s);
int			handle_triangle(char **values, t_scene *s);
int			handle_cone(char **values, t_scene *s);
int			handle_cube(char **values, t_scene *s);
void		save_scene(t_scene *s);
void		parse_scene(int fd, int *countrs, t_scene **s);
void		cleanup(char **values);

#endif