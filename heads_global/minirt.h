/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:11:07 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/27 09:02:51 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define DOUBLE_PREC 0.0001
# define INSTRUCTION_SET_SIZE 11
# define RES 0
# define AMB 1
# define CAM 2
# define LHT 3
# define SPH 4
# define PLA 5
# define SQU 6
# define CUB 7
# define TRI 8
# define CON 9
# define CYL 10

# define TRUE 1
# define FALSE 0

# include <math.h>
# include <pthread.h>
# include <errno.h>
//# include <error.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <unistd.h>
# include <stdbool.h>

# include "../lib/libft/libft.h"

typedef struct lightning_pack t_lightning_pack;
typedef	struct s_tmp t_tmp_m;
typedef struct light t_light;
typedef struct shape t_shape;

# include "../src/entities/tuple/tuple.h"
# include "../src/entities/material/material.h"
# include "../src/entities/matrix/matrix.h"
# include "../src/entities/ray/ray.h"
# include "../src/entities/light/light.h"
# include "../src/entities/color/colors.h"
# include "../src/entities/shapes/shape.h"
# include "../src/entities/shapes/cone/cone.h"
# include "../src/entities/shapes/cube/cube.h"
# include "../src/entities/shapes/cylinder/cylinder.h"
# include "../src/entities/shapes/plane/plane.h"
# include "../src/entities/shapes/sphere/sphere.h"
# include "../src/entities/shapes/triangle/triangle.h"
# include "../src/entities/shapes/square/square.h"
# include "../src/entities/intersection/intersection.h"
# include "../src/entities/bmp/bmp.h"
# include "../src/entities/camera/camera.h"

# include "../src/service/files/scene.h"
# include "../src/service/window/window.h"
# include "../src/service/errs/err.h"
# include "../src/service/free/free.h"

int		min(int a, int b);
int		max(int a, int b);
double	dmax(double a, double b);
double	dmin(double a, double b);
double	mins(double *a, int length);
double	maxs(double *a, int length);
void	swap(double *x, double *y);

/* DEBUG */
void	print_scene(t_scene *s);
void	print_camera(t_camera *cam);
void	print_light(t_light *l);
void	print_shape(t_shape *sh);
void	print_material(t_matrl *m);
void	print_matrix(t_matrix *m);
void	print_tuple(t_tuple *t);
void	print_world(t_world *w);
void	print_intersect_list(t_intersection_list *intersect);
void	print_intersection(t_intersection *intersect);
void	print_computations(t_computations *comp);
void	print_ray(t_ray *ray, int y, int x);
/* ***** */

#endif