/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/10/02 14:44:13 by sbocanci         ###   ########.fr       */
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

void		argb_render(t_camera *c, t_world *w, t_canvas *img);
void		fill_image(t_canvas *c, t_mlx_wrap *data, int count);
bool		display_scene(t_scene *s);
int			w_close(t_mlx_wrap *data);
int			k_press(int keycode, t_mlx_wrap *data);

#endif