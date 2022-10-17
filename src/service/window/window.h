/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/16 23:39:12 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include "../../../heads_global/minirt.h"

typedef struct mlx_wrap {
	void		*mlx;
	void		*win;
	void		**imgs;
	char		**addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_ptr;
	int			img_counter;
}	t_mlx_wrap;

void		*argb_render(t_camera *c, t_world *w, t_canvas *img);
void		my_mlx_pixel_put(t_mlx_wrap *data, unsigned int x, unsigned int y, int color, int count);
void		fill_image(t_canvas *c, t_mlx_wrap *data, int count);
void		display_scene(t_scene *s);
//int             wclose(int keycode, s_mlx_win *vars);

#endif