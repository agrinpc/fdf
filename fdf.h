/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:39:49 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/05 22:58:57 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# define WIDTH 1920
# define HEIGHT 1080
# define MARGIN 100

typedef struct s_probs
{
	int		w;
	int 	h;
	int		**data;
	int		map;
	double	alpha;
	double	beta;
	double	gamma;
	double	xlen;
	double	ylen;
	double	zscale;
	double	baseX;
	double	baseY;
	int		state;
}				t_probs;

typedef struct	s_data
{
	void	*mlx;
	void	*img;
	void	*mlx_win;
	char	*addr;
	t_probs	*prob;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_double_point
{
	t_point start;
	t_point	end;
}				t_double_point;

typedef struct	s_circle
{
	t_point center;
	int		r;
}				t_circle;

t_point			create_point(double x, double y);
t_double_point	create_double_point(double x1, double y1, double x2, double y2);
t_circle		create_circle(int x, int y, int r);
t_probs			get_data(char	*file);
void 			make_data(t_probs *probs);
int				get_width(char *str);
int				get_height(char *str);
int				**get_points(int w, int h, char *str);
char			*get_str(int	map);
void			print_data(t_probs prob);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_line(t_data *data, t_double_point line);
void			draw_circle(t_data *data, t_circle circle);
void			print_points(t_probs prob, t_data *data);
void			print_data(t_probs prob);
void			draw_lines(t_probs prob, t_data *data);
void			draw_vertical_line(t_data *data, t_double_point line);
void			draw_horizental_line(t_data *data, t_double_point line);
void			zoom(t_data *data, double zoom);
void			draw_center(t_data *data);

#endif