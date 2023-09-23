/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 18:36:42 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H
# include "../../../heads_global/minirt.h"

bool	check_arguments(t_scene *s, int ac, char **av);
void	check_resolution(int **counters_ptr, int *is_correct, char **str);
void	check_ambiance(int **counters_ptr, int *is_correct, char **str);
void	check_cameras(int **counters_ptr, int *is_correct, char **str);
void	check_lights(int **counters_ptr, int *is_correct, char **str);
void	check_sphere(int **counters_ptr, int *is_correct, char **str);
void	check_plane(int **counters_ptr, int *is_correct, char **str);
void	check_square_cube(int **counters_ptr, int *is_correct, char **str);
void	check_triangle(int **counters_ptr, int *is_correct, char **str);
void	check_cone_cylinder(int **counters_ptr, int *is_correct, char **str);

#endif