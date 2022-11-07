/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:44:32 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:45:23 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	key_down(t_data *data)
{
	if (data->prob->mode == 0)
		data->prob->by += 5;
	if (data->prob->mode == 1)
		data->prob->a -= 0.05;
	if (data->prob->mode == 2)
		data->prob->b -= 0.05;
	if (data->prob->mode == 3)
		data->prob->g -= 0.01;
	if (data->prob->mode == 4)
		zoom(data, (double)49 / (double)50);
	if (data->prob->mode == 5)
		data->prob->zs -= 0.5;
}

int	print_key(int key, t_data *data)
{
	if (key == 6 || key == 7 || key == 16 || key == 1 || key == 0 || key == 46)
		set_mode(key, data);
	if (key == 126)
		key_up(data);
	if (key == 125)
		key_down(data);
	if (key == 124)
		data->prob->bx += 5;
	if (key == 123)
		data->prob->bx -= 5;
	if (key == 15)
		reset(data);
	if (key == 53)
		closing(data);
	data->prob->state = 1;
	return (0);
}

void	draw_center(t_data *data)
{
	int	j;

	j = -1;
	while (++j < 4)
	{
		my_mlx_pixel_put(data, WD / 2 + j, HG / 2, 0x00FF0000);
		my_mlx_pixel_put(data, WD / 2 - j, HG / 2, 0x00FF0000);
		my_mlx_pixel_put(data, WD / 2, HG / 2 + j, 0x00FF0000);
		my_mlx_pixel_put(data, WD / 2, HG / 2 - j, 0x00FF0000);
	}
}

void	reset(t_data *data)
{
	data->prob->a = 0;
	data->prob->b = 0;
	data->prob->g = 0;
	data->prob->bx = 0;
	data->prob->by = 0;
	data->prob->zs = 5;
	data->prob->bs = 1;
}

int	closing(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->prob->h)
		free(data->prob->d[i]);
	free(data->prob->d);
	mlx_destroy_image(data->mlx, data->img);
	exit(0);
}
