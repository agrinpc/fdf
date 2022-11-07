/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:40:00 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:45:35 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

t_point	create_point(double x, double y)
{
	t_point	point;

	point.x = floorf(x * 10) / 10;
	point.y = floorf(y * 10) / 10;
	return (point);
}

t_d_point	create_d_pt(double x1, double y1, double x2, double y2)
{
	t_d_point	d_point;

	d_point.start = create_point(x1, y1);
	d_point.end = create_point(x2, y2);
	return (d_point);
}

t_circle	create_circle(int x, int y, int r)
{
	t_circle	circle;
	t_point		point;

	point = create_point(x, y);
	circle.center = point;
	circle.r = r;
	return (circle);
}

t_probs	get_data(char	*file)
{
	t_probs	probs;

	probs.map = open(file, O_RDONLY);
	make_data(&probs);
	probs.xl = (WD - 2 * MG) / (probs.w - 1);
	probs.yl = (HG - 2 * MG) / (probs.h - 1);
	probs.mx = get_max_z(probs.d, probs.w, probs.h);
	probs.bs = 1;
	probs.a = 0;
	probs.b = 0;
	probs.g = 0;
	probs.zs = 5;
	probs.state = 1;
	probs.bx = 0;
	probs.by = 0;
	probs.mode = 0;
	return (probs);
}

void	make_data(t_probs *probs)
{
	char	*str;

	str = get_str(probs->map);
	probs->w = get_width(str);
	probs->h = get_height(str);
	probs->d = get_points(probs->w, probs->h, str);
	free(str);
}
