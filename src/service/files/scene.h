/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sv <sv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/17 20:21:51 by sv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../../../heads_global/minirt.h"
# define COLOR_CF 0.003921569 //WHY?
# define SHAPES 1
# define ALL 2

typedef struct scene
{
	int			resolution_x;
	int			resolution_y;
	double		ambi_ratio;
	t_tuple		ambi_color;
	int			camera_counter;
	t_camera	**cameras;
	int			light_counter;
	t_light		**lights;
	int			shape_counter;
	t_shape		**shapes;
}	t_scene;

void	init_scene(int *counters, t_scene *scene);
void	set_tuple(t_tuple *tuple, char *value, char type);
void	free_scene(t_scene *s);
void	handle_r(char **input, t_scene *s);
void	handle_a(char **input, t_scene *s);
void	handle_c(char **input, t_scene *s);
void	handle_l(char **input, t_scene *s);
void	handle_line(char **input, t_scene *s);
void	handle_plane(char **values, t_scene *s);
void	handle_sphere(char **values, t_scene *s);
void	handle_square(char **values, t_scene *s);
void	handle_cylinder(char **values, t_scene *s);
void	handle_triangle(char **values, t_scene *s);
void	handle_cone(char **values, t_scene *s);
void	handle_cube(char **values, t_scene *s);
void	save_scene(t_scene *s, int *fd_list);
void	parse_scene(int fd, int *counters, t_scene *s);
void	cleanup(char **values);
int		*create_files(int *counters);

/* DEBUG */
void	print_scene(t_scene *s);
/* ***** */

#endif