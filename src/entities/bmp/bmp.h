/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/02 16:57:29 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H
# include "../../../heads_global/minirt.h"

typedef struct t_canvas
{
	unsigned int	w;
	unsigned int	h;
	unsigned int	**canvas;
}	s_canvas;

s_canvas	*canvas_canvas(unsigned int w, unsigned int h);
void		canvas_free(s_canvas *c);
int			init_bmp(int h, int w, int fd);
void		fill_bmp(int fd, s_canvas *c);

#endif //RT_CHALLENGE_BMP_H
