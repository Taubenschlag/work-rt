/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:08:27 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../../../heads_global/minirt.h"

# define SHAPES 1
# define ALL 2
# define COLOR_CF 0.003921569
/* COLOR_CF: Color correction factor. Converting from [0-255] to [0-1] range */

/*
** This structure holds all necessary parametrs to render a scene
*/
typedef struct scene
{
	int			fd_infile;
	char		*filename;
	int			counters[INSTRUCTION_SET_SIZE];
	int			res_x;
	int			res_y;
	double		ambi_ratio;
	t_tuple		ambi_color;
	int			camera_count;
	t_camera	**cameras;
	int			light_count;
	t_light		**lights;
	int			shape_count;
	t_shape		**shapes;
	int			*fd_list;
}	t_scene;

/*
** The following structure holds temporary parameters
** usaed during scene parsing and object creation
** as intermediate value holders
** Maynly used in functions from scene_handlers_123.c 
*/
typedef struct s_tmp_pars
{
	double		light_br;
	double		sph_d;
	t_tuple		center;
	t_tuple		direct;
	t_tuple		color;
	t_tuple		tup;
	t_tuple		norm;
	t_matrix	m;
	t_matrix	m_cpy;
	t_matrix	trans;
}	t_tmp;

bool	init_scene(t_scene *scene);
void	set_tuple(t_tuple *tuple, char *value, char type);
bool	handle_r(char **input, t_scene *s);
bool	handle_a(char **input, t_scene *s);
bool	handle_c(char **input, t_scene *s);
bool	handle_l(char **input, t_scene *s);
bool	handle_line(char **input, t_scene *s);
bool	handle_plane(char **values, t_scene *s);
bool	handle_sphere(char **values, t_scene *s);
bool	handle_square(char **values, t_scene *s);
bool	handle_cylinder(char **values, t_scene *s);
bool	handle_triangle(char **values, t_scene *s);
bool	handle_cone(char **values, t_scene *s);
bool	handle_cube(char **values, t_scene *s);
bool	save_scene(t_scene *s, int *fd_list);
bool	parse_scene(t_scene *s);
bool	create_files(t_scene *s);

#endif