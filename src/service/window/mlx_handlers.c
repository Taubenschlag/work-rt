/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:28:25 by rokupin           #+#    #+#             */
/*   Updated: 2022/10/17 17:39:58 by rokupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../heads_global/minirt.h"

void	went_out(t_mlx_wrap *data)
{
	int	i;

	i = 1;
	free(data->imgs[0]);
	free(data->imgs[data->img_counter + 1]);
	while (i <= data->img_counter)
	{
		mlx_destroy_image(data->mlx, data->imgs[i]);
		i++;
	}
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	free(data);
	exit(EXIT_SUCCESS);
}

int	w_close(t_mlx_wrap *data)
{
	went_out(data);
	return (1);
}

int	k_press(int keycode, t_mlx_wrap *data)
{
	int	next;
	int	prev;

	next = data->img_ptr + 1;
	prev = data->img_ptr - 1;
	if (keycode == 65307)
		went_out(data);
	if (keycode == 65363 && data->imgs[next])
	{
		mlx_put_image_to_window(
			data->mlx, data->win, data->imgs[next], 0, 0);
		data->img_ptr++;
	}
	else if (keycode == 65361 && data->imgs[prev])
	{
		mlx_put_image_to_window(
			data->mlx, data->win, data->imgs[prev], 0, 0);
		data->img_ptr--;
	}
	else
		return (0);
	return (1);
}
