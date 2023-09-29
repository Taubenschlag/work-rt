/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:36:32 by sbocanci          #+#    #+#             */
/*   Updated: 2023/09/29 18:58:25 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "../../../heads_global/minirt.h"

/* free.c */
void	free_scene(t_scene *s);
void	cleanup(char **values);
void	emergency_close(int *fds, int failed);
void	canvas_free(t_canvas *c);
void	free_camera(t_camera *c);

/* free_intersect.c */
void	intersection_list_free(t_intersection_list **l);
void	free_unsorted_list(int size, t_intersection_list *unsorted[size]);

#endif