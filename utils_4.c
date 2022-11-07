/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:41:00 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:43:52 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	print_scale(t_data *data)
{
	t_probs	prob;
	char	*scale;
	char	*zscale;

	scale = ft_strjoin_1(ft_itoa(prob.bs), ".");
	scale = ft_strjoin_2(scale, ft_itoa((int)(prob.bs * 10) % 10));
	zscale = ft_strjoin_1(ft_itoa(prob.zs), ".");
	zscale = ft_strjoin_2(zscale, ft_itoa((int)(prob.zs * 10) % 10));
	prob = *(data->prob);
	mlx_string_put(data->mlx, data->mlx_win, 30, 100, 0x00ffba08, "Scale: ");
	mlx_string_put(data->mlx, data->mlx_win, 90, 100, 0x00ef233c, scale);
	mlx_string_put(data->mlx, data->mlx_win, 30, 120, 0x00ffba08, "Z Scale: ");
	mlx_string_put(data->mlx, data->mlx_win, 90, 120, 0x00ef233c, zscale);
	free(scale);
	free(zscale);
}

void	print_data(t_data *data)
{
	t_probs	prob;
	char	*angl;

	prob = *(data->prob);
	angl = ft_itoa(prob.a * 180 / M_PI);
	mlx_string_put(data->mlx, data->mlx_win, 30, 40, 0x00ffba08, "XAngle: ");
	mlx_string_put(data->mlx, data->mlx_win, 90, 40, 0x00ef233c, angl);
	free(angl);
	angl = ft_itoa(prob.b * 180 / M_PI);
	mlx_string_put(data->mlx, data->mlx_win, 30, 60, 0x00ffba08, "YAngle: ");
	mlx_string_put(data->mlx, data->mlx_win, 90, 60, 0x00ef233c, angl);
	free(angl);
	angl = ft_itoa(prob.g * 180 / M_PI);
	mlx_string_put(data->mlx, data->mlx_win, 30, 80, 0x00ffba08, "ZAngel: ");
	mlx_string_put(data->mlx, data->mlx_win, 90, 80, 0x00ef233c, angl);
	free(angl);
	print_scale(data);
}

t_d_point	get_first_point(t_probs p, int i, int j)
{
	t_d_point	pt;
	double		y1;
	double		y2;
	double		x1;
	double		x2;

	y1 = -p.d[i][j] * sin(p.a) * cos(p.b) * p.zs * p.bs
		+ (i * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * cos(p.g)
		+ (j * p.xl * p.bs - WD / 2 + MG) * sin(p.g) * cos(p.b);
	y2 = -p.d[i + 1][j] * sin(p.a) * cos(p.b) * p.zs * p.bs
		+ ((i + 1) * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * cos(p.g)
		+ (j * p.xl * p.bs - WD / 2 + MG) * sin(p.g) * cos(p.b);
	x1 = p.d[i][j] * sin(p.b) * cos(p.a) * p.zs * p.bs
		+ (j * p.xl * p.bs - WD / 2 + MG) * cos(p.b) * cos(p.g)
		- (i * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * sin(p.g);
	x2 = p.d[i + 1][j] * sin(p.b) * cos(p.a) * p.zs * p.bs
		+ (j * p.xl * p.bs - WD / 2 + MG) * cos(p.b) * cos(p.g)
		- ((i + 1) * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * sin(p.g);
	pt = create_d_pt(x1 + p.bx, y1 + p.by, x2 + p.bx, y2 + p.by);
	return (pt);
}

t_d_point	get_second_point(t_probs p, int i, int j)
{
	t_d_point	pt;
	double		y1;
	double		y2;
	double		x1;
	double		x2;

	y1 = -p.d[j][i] * sin(p.a) * cos(p.b) * p.zs * p.bs
		+ (j * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * cos(p.g)
		+ (i * p.xl * p.bs - WD / 2 + MG) * sin(p.g) * cos(p.b);
	y2 = -p.d[j][i + 1] * sin(p.a) * cos(p.b) * p.zs * p.bs
		+ (j * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * cos(p.g)
		+ ((i + 1) * p.xl * p.bs - WD / 2 + MG) * sin(p.g) * cos(p.b);
	x1 = p.d[j][i] * sin(p.b) * cos(p.a) * p.zs * p.bs
		+ (i * p.xl * p.bs - WD / 2 + MG) * cos(p.b) * cos(p.g)
		- (j * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * sin(p.g);
	x2 = p.d[j][i + 1] * sin(p.b) * cos(p.a) * p.zs * p.bs
		+ ((i + 1) * p.xl * p.bs - WD / 2 + MG) * cos(p.b) * cos(p.g)
		- (j * p.yl * p.bs - HG / 2 + MG) * cos(p.a) * sin(p.g);
	pt = create_d_pt(x1 + p.bx, y1 + p.by, x2 + p.bx, y2 + p.by);
	return (pt);
}

void	draw_lines(t_probs p, t_data *d)
{
	t_d_point	pt;
	int			i;
	int			j;

	i = -1;
	while (++i < p.h - 1)
	{
		j = -1;
		while (++j < p.w)
		{
			pt = get_first_point(p, i, j);
			dr_ln(d, pt, get_cl(p.d[i][j], p.mx), get_cl(p.d[i + 1][j], p.mx));
		}
	}
	i = -1;
	while (++i < p.w - 1)
	{
		j = -1;
		while (++j < p.h)
		{
			pt = get_second_point(p, i, j);
			dr_ln(d, pt, get_cl(p.d[j][i], p.mx), get_cl(p.d[j][i + 1], p.mx));
		}
	}
	d->prob->state = 0;
}
