/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:11:07 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/04 14:24:29 by sbocanci         ###   ########.fr       */
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
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <unistd.h>
# include <stdbool.h>

# include "../lib/libft/libft.h"

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

#endif
