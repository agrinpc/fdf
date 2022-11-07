/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:41:07 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:44:16 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_img(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (++i < HG)
	{
		j = 0;
		while (++j < WD)
			my_mlx_pixel_put(data, j, i, 0x00000000);
	}
}

void	draw_vertical_line(t_data *data, t_d_point line, int cl1, int cl2)
{
	double	x;
	double	y;
	double	s;

	x = line.start.x + WD / 2;
	y = line.start.y + HG / 2;
	s = 1;
	if (line.start.y > line.end.y)
		s = -1;
	if (x < WD - 1 && x > 1 && y < HG - 1 && y > 1)
		my_mlx_pixel_put(data, x, y, set_color(cl1, cl2, line, x));
	while (y != line.end.y + HG / 2 && s * y <= s * (line.end.y + HG / 2))
	{
		y += s;
		if (x < WD - 1 && x > 1 && y < HG - 1 && y > 1)
			my_mlx_pixel_put(data, x, y, set_color(cl1, cl2, line, x));
	}
}

void	draw_horizental_line(t_data *data, t_d_point line, int cl1, int cl2)
{
	double	x;
	double	y;
	double	s;

	x = line.start.x + WD / 2;
	y = line.start.y + HG / 2;
	s = 1;
	if (line.start.x > line.end.x)
		s = -1;
	if (x < WD - 1 && x > 1 && y < HG - 1 && y > 1)
		my_mlx_pixel_put(data, x, y, set_color(cl1, cl2, line, x));
	while (x != line.end.x + WD / 2 && s * x <= s * (line.end.x + WD / 2))
	{
		x += s;
		if (x < WD - 1 && x > 1 && y < HG - 1 && y > 1)
			my_mlx_pixel_put(data, x, y, set_color(cl1, cl2, line, x));
	}
}

int	set_color(int cl1, int cl2, t_d_point line, double x)
{
	int		r;
	int		g;
	int		b;
	double	m;

	m = (x - line.start.x - WD / 2) / (line.start.x - line.end.x);
	r = cl1 / (256 * 256) + (int)(((cl1 - cl2) / (256 * 256)) * m);
	cl1 = cl1 % (256 * 256);
	cl2 = cl2 % (256 * 256);
	g = cl1 / 256 + (int)(((cl1 - cl2) / 256) * m);
	cl1 = cl1 % (256);
	cl2 = cl2 % (256);
	b = cl1 + (int)((cl1 - cl2) * m);
	return (r * 256 * 256 + g * 256 + b);
}
