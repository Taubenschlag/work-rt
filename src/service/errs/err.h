/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/13 21:31:20 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H
# include "../../../heads_global/minirt.h"

int		check_arguments(int ac, char **av);
int		*check_file(char *filename);
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