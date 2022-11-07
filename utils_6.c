/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:41:21 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:45:01 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	dr_diag_ln(t_data *data, t_point *pt, int cl, double m)
{
	double	y0;
	double	n;

	y0 = pt->y;
	pt->y = pt->y + 0.015 / m;
	n = (pt->y - y0) / fabs(pt->y - y0);
	while (n * y0 < n * pt->y)
	{
		if (pt->x <= WD - 1 && pt->x >= 1 && y0 < HG - 1 && y0 > 1)
			my_mlx_pixel_put(data, pt->x, y0, cl);
		y0 += n;
	}
}

void	dr_ln(t_data *data, t_d_point line, int cl1, int cl2)
{
	t_point	pt;
	double	m;
	double	s;

	if (fabs(line.start.y - line.end.y) < 0.01)
	{
		draw_horizental_line(data, line, cl1, cl2);
		return ;
	}
	if (fabs(line.start.x - line.end.x) < 0.01)
	{
		draw_vertical_line(data, line, cl1, cl2);
		return ;
	}
	m = (line.start.x - line.end.x) / (line.start.y - line.end.y);
	pt = create_point(line.start.x + WD / 2, line.start.y + HG / 2);
	s = (line.end.x - line.start.x) / fabs(line.end.x - line.start.x);
	if (pt.x < WD - 1 && pt.x > 1 && pt.y < HG - 1 && pt.y > 1)
		my_mlx_pixel_put(data, pt.x, pt.y, cl1);
	while (s * pt.x <= s * (line.end.x + WD / 2))
	{
		pt.x += 0.015 * s;
		dr_diag_ln(data, &pt, set_color(cl1, cl2, line, pt.x), s * m);
	}
}

void	zoom(t_data *data, double zoom_val)
{
	data->prob->bs *= zoom_val;
}

void	set_mode(int key, t_data *data)
{
	if (key == 6)
		data->prob->mode = 3;
	if (key == 7)
		data->prob->mode = 1;
	if (key == 16)
		data->prob->mode = 2;
	if (key == 1)
		data->prob->mode = 4;
	if (key == 0)
		data->prob->mode = 5;
	if (key == 46)
		data->prob->mode = 0;
}

void	key_up(t_data *data)
{
	if (data->prob->mode == 0)
		data->prob->by -= 5;
	if (data->prob->mode == 1)
		data->prob->a += 0.05;
	if (data->prob->mode == 2)
		data->prob->b += 0.05;
	if (data->prob->mode == 3)
		data->prob->g += 0.01;
	if (data->prob->mode == 4)
		zoom(data, (double)50 / (double)49);
	if (data->prob->mode == 5)
		data->prob->zs += 0.5;
}
