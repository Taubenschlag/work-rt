/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:36:32 by sbocanci          #+#    #+#             */
/*   Updated: 2023/09/23 19:19:05 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "../../../heads_global/minirt.h"

void	free_scene(t_scene *s);
void	cleanup(char **values);
void	emergency_close(int *fds, int failed);
void	canvas_free(t_canvas *c);
void	free_camera(t_camera *c);

#endif