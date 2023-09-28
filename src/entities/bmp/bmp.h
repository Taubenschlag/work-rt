/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:08:19 by rokupin           #+#    #+#             */
/*   Updated: 2023/09/23 14:51:42 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H
# include "../../../heads_global/minirt.h"

typedef struct canvas
{
	unsigned int	w;
	unsigned int	h;
	unsigned int	**canvas;
}	t_canvas;

void		init_canvas(unsigned int w, unsigned int h, t_canvas *c);
int			init_bmp(int h, int w, int fd);
void		fill_bmp(int fd, t_canvas *c);

#endif
