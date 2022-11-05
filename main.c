/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:39:37 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/06 00:15:56 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

t_point	create_point(double x, double y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}

t_double_point	create_double_point(double x1, double y1, double x2, double y2)
{
	t_double_point	d_point;

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
	probs.xlen = (WIDTH - MARGIN) / probs.w;
	probs.ylen = (HEIGHT - MARGIN) / probs.h;
	probs.alpha = 0;
	probs.beta = 0;
	probs.gamma = 0;
	probs.zscale = 3.5;
	probs.state = 1;
	probs.baseX = 0;
	probs.baseY = 0;
	return (probs);
}

void make_data(t_probs *probs)
{
	char	*str;

	printf("make_data:\n");
	str = get_str(probs->map);
	probs->w = get_width(str);
	probs->h = get_height(str);
	probs->data = get_points(probs->w, probs->h, str);
}

int	get_height(char *str)
{
	int	i;
	int	res;

	printf("get_height:\n");
	i = -1;
	res = 0;
	while (str[++i])
		if (str[i] == '\n')
			res++;
	printf("DONE: w = %d\n", res);
	return (res);
}

int	get_width(char *str)
{
	int	i;
	int	res;

	printf("get_width:\n");
	i = -1;
	res = 0;
	while (str[++i] && str[i] != '\n')
		if (str[i] == ' ')
		{
			res++;
			while (str[++i] && str[i] == ' ')
				;
			i--;
		}
	printf("DONE: h = %d\n", res);
	return (res);		
}

int	**get_points(int w, int h, char *str)
{
	int		i;
	int		j;
	char	**row;
	char	**rows;
	int		**data;

	i = -1;
	rows = ft_split(str, '\n');
	data = malloc(h * sizeof(char *));
	while (++i < w)
		data[i] = malloc(w * sizeof(int));
	i = -1;
	while (++i < h)
	{
		row = ft_split(rows[i], ' ');
		j = -1;
		while (++j < w)
			data[i][j] = ft_atoi(row[j]);
		free(row);
	}
	free(rows);
	return (data);
}

char	*get_str(int	map)
{
	char	*res;
	char	*cur;
	printf("get_str:\n");
	cur = get_next_line(map);
	while(cur)
	{
		res = ft_strjoin(res, cur);
		free(cur);
		cur = get_next_line(map);
	}
	printf("DONE\n");
	return (res);
}

void	print_data(t_probs prob)
{
	int	i;
	int	j;
	
	i = -1;
	printf("print_data:\n");
	printf("w = %d\n", prob.w);
	while (++i < prob.h)
	{
		j = -1;
		while (++j < prob.w)
			printf("%2d ", prob.data[i][j]);
		printf("\n");
	}
	printf("end of data\n");
}

void	print_points(t_probs prob, t_data *data)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = -1;
	printf("Drawing points:\n");
	while (++i < prob.h)
	{
		j = -1;
		while (++j < prob.w)
		{
			x = MARGIN + (j * prob.xlen);
			y = MARGIN + (i * prob.ylen);
			my_mlx_pixel_put(data, x, y, 0x006a994e);
		}
	}
}

void	draw_lines(t_probs prob, t_data *data)
{
	t_double_point	point;
	int				i;
	int				j;
	double			y1;
	double			y2;
	double			x1;
	double			x2;

	i = -1;
	while (++i < prob.h - 1)
	{
		j = -1;
		while (++j < prob.w)
		{
			y1 = -prob.data[i][j] * sin(prob.alpha) * cos(prob.beta) * prob.zscale + (i * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * cos(prob.gamma) + (j * prob.xlen - WIDTH / 2 + MARGIN) * sin(prob.gamma) * cos(prob.beta);
			y2 = -prob.data[i + 1][j] * sin(prob.alpha) * cos(prob.beta) * prob.zscale + ((i + 1) * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * cos(prob.gamma) + (j * prob.xlen - WIDTH / 2 + MARGIN) * sin(prob.gamma) * cos(prob.beta);
			x1 = prob.data[i][j] * sin(prob.beta) * cos(prob.alpha) * prob.zscale + (j * prob.xlen - WIDTH / 2 + MARGIN) * cos(prob.beta) * cos(prob.gamma) - (i * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * sin(prob.gamma);
			x2 = prob.data[i + 1][j] * sin(prob.beta) * cos(prob.alpha) * prob.zscale + (j * prob.xlen - WIDTH / 2 + MARGIN) * cos(prob.beta) * cos(prob.gamma)  - ((i + 1) * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * sin(prob.gamma);
			point = create_double_point(x1 + prob.baseX, y1 + prob.baseY, x2 + prob.baseX, y2 + prob.baseY);
			// printf("(%f, %f), (%f, %f)\n", point.start.x + WIDTH / 2, point.start.y + HEIGHT / 2, point.end.x + WIDTH / 2, point.end.y + HEIGHT / 2);
			draw_line(data, point);
		}
	}
	i = -1;
	while (++i < prob.w - 1)
	{
		j = -1;
		while (++j < prob.h)
		{
			y1 = -prob.data[j][i] * sin(prob.alpha) * cos(prob.beta) * prob.zscale + (j * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * cos(prob.gamma) + (i * prob.xlen - WIDTH / 2 + MARGIN) * sin(prob.gamma) * cos(prob.beta);
			y2 = -prob.data[j][i + 1] * sin(prob.alpha) * cos(prob.beta) * prob.zscale + (j * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * cos(prob.gamma) + ((i + 1) * prob.xlen - WIDTH / 2 + MARGIN) * sin(prob.gamma) * cos(prob.beta);
			x1 = prob.data[j][i] * sin(prob.beta) * cos(prob.alpha) * prob.zscale + (i * prob.xlen - WIDTH / 2 + MARGIN)  * cos(prob.beta) * cos(prob.gamma)- (j * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * sin(prob.gamma);
			x2 = prob.data[j][i + 1] * sin(prob.beta) * cos(prob.alpha) * prob.zscale + ((i + 1) * prob.xlen - WIDTH / 2 + MARGIN)  * cos(prob.beta) * cos(prob.gamma) - (j * prob.ylen - HEIGHT / 2 + MARGIN) * cos(prob.alpha) * sin(prob.gamma);
			point = create_double_point(x1 + prob.baseX, y1 + prob.baseY, x2 + prob.baseX, y2 + prob.baseY);
			// printf("(%f, %f), (%f, %f)\n", point.start.x + WIDTH / 2, point.start.y + HEIGHT / 2, point.end.x + WIDTH / 2, point.end.y + HEIGHT / 2);
			draw_line(data, point);
		}
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_vertical_line(t_data *data, t_double_point line)
{
	double	x;
	double	y;
	double	s;

	x = line.start.x + WIDTH / 2;
	y = line.start.y + HEIGHT / 2;
	s = 1;
	if (line.start.y > line.end.y)
		s = -1;
	if (x < WIDTH - 1 && x > 1 && y < HEIGHT - 1 && y > 1)
		my_mlx_pixel_put(data, x, y, 0x00f2e8cf);
	while (y != line.end.y + HEIGHT / 2 && s * y <= s * (line.end.y + HEIGHT / 2))
	{
		y += s;
		if (x < WIDTH - 1 && x > 1 && y < HEIGHT - 1 && y > 1)
			my_mlx_pixel_put(data, x, y, 0x00f2e8cf);
	}
}

void	draw_horizental_line(t_data *data, t_double_point line)
{
	double	x;
	double	y;
	double	s;

	printf("Gamma = %f\n", data->prob->gamma);
	x = line.start.x + WIDTH / 2;
	y = line.start.y + HEIGHT / 2;
	s = 1;
	if (line.start.x > line.end.x)
		s = -1;
	if (x < WIDTH - 1 && x > 1 && y < HEIGHT - 1 && y > 1)
		my_mlx_pixel_put(data, x, y, 0x00f2e8cf);
	while (x != line.end.x + WIDTH / 2 && s * x <= s * (line.end.x + WIDTH / 2))
	{
		x += s;
		if (x < WIDTH - 1 && x > 1 && y < HEIGHT - 1 && y > 1)
			my_mlx_pixel_put(data, x, y, 0x00f2e8cf);
	}
}

void	draw_line(t_data *data, t_double_point line)
{
	double	m;
	double	x;
	double	y;
	double	s;
	double	y0;

	if (line.start.y - line.end.y == 0)
	{
		draw_horizental_line(data, line);
		return ;
	}
	if (line.start.x - line.end.x == 0)
	{
		draw_vertical_line(data, line);
		return ;
	}
	m = (line.start.x - line.end.x) / (line.start.y - line.end.y);
	x = line.start.x + WIDTH / 2;
	y = line.start.y + HEIGHT / 2;
	s = 1;
	if (line.start.x > line.end.x)
		s = -1;
	if (x < WIDTH - 1 && x > 1 && y < HEIGHT - 1 && y > 1)
		my_mlx_pixel_put(data, x, y, 0x0000FF00);
	while (s * x <= s * (line.end.x + WIDTH / 2))
	{
		x += s;
		y0 = y;
		y = y + s / m;
		if (y > y0)
			while (y0 < y)
			{
				if (x <= WIDTH - 1 && x >= 1 && y0 < HEIGHT - 1 && y0 > 1)
					my_mlx_pixel_put(data, x, y0, 0x00f2e8cf);
				y0 += 1;
			}
		else
			while (y < y0)
			{
				if (x <= WIDTH - 1 && x >= 1 && y0 > 1 && y0 < HEIGHT - 1)
					my_mlx_pixel_put(data, x, y0, 0x00f2e8cf);
				y0 -= 1;
			}
	}
}

void	zoom(t_data *data, double zoom)
{
	data->prob->xlen *= zoom;
	data->prob->ylen *= zoom;
	data->prob->zscale *= zoom;
}

int	print_key(int key, t_data *data)
{
	printf("%d is pressed\n", key);
	if (key == 12)
		data->prob->alpha += 0.05;
	if (key == 13)
		data->prob->alpha -= 0.05;
	if (key == 0)
		data->prob->beta += 0.05;
	if (key == 1)
		data->prob->beta -= 0.05;
	if (key == 6)
		data->prob->gamma += 0.02;
	if (key == 7)
		data->prob->gamma -= 0.02;
	if (key == 124)
		data->prob->baseX += 5;
	if (key == 123)
		data->prob->baseX -= 5;
	if (key == 125)
		data->prob->baseY += 5;
	if (key == 126)
		data->prob->baseY -= 5;
	if (key == 30)
		zoom(data,	(double)10 / (double)9);
	if (key == 33)
		zoom(data,	(double)9 / (double)10);
	data->prob->state = 1;
	return (0);
}

void	draw_center(t_data *data)
{
	int	j;

	j = -1;
	while (++j < 4)
	{
		my_mlx_pixel_put(data, WIDTH / 2 + j, HEIGHT / 2, 0x00FF0000);
		my_mlx_pixel_put(data, WIDTH / 2 - j, HEIGHT / 2, 0x00FF0000);
		my_mlx_pixel_put(data, WIDTH / 2, HEIGHT / 2 + j, 0x00FF0000);
		my_mlx_pixel_put(data, WIDTH / 2, HEIGHT / 2 - j, 0x00FF0000);
	}
}

void	draw_circle(t_data *data, t_circle circle)
{
	double	dx;
	double	s;
	double	y1;
	double	dy;

	dx = -circle.r;
	y1 = 0;
	s = 0.1;
	while (dx <= 0)
	{
		dy = y1;
		y1 = floorl(sqrt(pow(circle.r, 2) - pow(dx, 2)) * 10) / 10;
		while (dy <= y1)
		{
			my_mlx_pixel_put(data, dx + circle.center.x, dy + circle.center.y, 0x00FF0000);
			my_mlx_pixel_put(data, dx + circle.center.x, -dy + circle.center.y, 0x00FF0000);
			dy += 0.1;
		}
		dx += s;
	}
	y1 = circle.r;
	while (dx <= circle.r)
	{
		dy = y1;
		y1 = floorl(sqrt(pow(circle.r, 2) - pow(dx, 2)) * 10) / 10;
		while (dy >= y1)
		{
			my_mlx_pixel_put(data, dx + circle.center.x, dy + circle.center.y, 0x00FF0000);
			my_mlx_pixel_put(data, dx + circle.center.x, -dy + circle.center.y, 0x00FF0000);
			dy -= 0.1;
		}
		dx += s;
	}
	dy = 3.1;
	y1 = 0;
	while (dy >= y1)
	{
		my_mlx_pixel_put(data, dx + circle.center.x, dy + circle.center.y, 0x00FF0000);
		my_mlx_pixel_put(data, dx + circle.center.x, -dy + circle.center.y, 0x00FF0000);
		dy -= 0.1;
	}
}

int	render(t_data *img)
{
	t_probs	probs;

	probs = *(img->prob);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	if (probs.state)
	{
		draw_center(img);
		draw_lines(probs, img);
		probs.state = 0;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv )
{
	t_data			img;
	t_probs			probs;
	
	if (argc < 1)
		return (0);
	probs = get_data(argv[1]);
	print_data(probs);
	img.mlx = mlx_init();
	img.prob = &probs;
	img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Milad");
	img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mlx_hook(img.mlx_win, 2, 0, print_key, &img);
	mlx_loop_hook(img.mlx, render, &img);
	mlx_loop(img.mlx);
}
