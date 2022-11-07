/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:39:49 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:53:38 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"
# define WD 1920
# define HG 1080
# define MG 100

typedef struct s_probs
{
	int		w;
	int		h;
	int		**d;
	int		map;
	double	a;
	double	b;
	double	g;
	double	xl;
	double	yl;
	double	zs;
	double	bx;
	double	by;
	double	bs;
	int		mx;
	int		state;
	int		mode;
}				t_probs;

typedef struct s_data
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

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_double_point
{
	t_point	start;
	t_point	end;
}				t_d_point;

typedef struct s_circle
{
	t_point	center;
	int		r;
}				t_circle;

t_point		create_point(double x, double y);
t_d_point	create_d_pt(double x1, double y1, double x2, double y2);
t_circle	create_circle(int x, int y, int r);
t_probs		get_data(char	*file);
void		make_data(t_probs *probs);
int			get_width(char *str);
int			get_height(char *str);
int			**get_points(int w, int h, char *str);
char		*get_str(int map);
void		log_data(t_probs prob);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		dr_ln(t_data *data, t_d_point line, int color1, int color2);
void		draw_circle(t_data *data, t_circle circle);
void		print_points(t_probs prob, t_data *data);
void		draw_lines(t_probs prob, t_data *data);
void		draw_vertical_line(t_data *data,
				t_d_point line, int color1, int color2);
void		draw_horizental_line(t_data *data,
				t_d_point line, int color1, int color2);
void		zoom(t_data *data, double zoom);
void		draw_center(t_data *data);
void		clear_img(t_data *data);
int			closing(t_data *data);
int			mouse_hooks(int key, t_data *data);
void		reset(t_data *data);
void		print_mode(t_data *data);
void		print_data(t_data *data);
void		print_scale(t_data *data);
int			get_max_z(int **numbers, int w, int h);
int			set_color(int color1, int color2, t_d_point line, double x);
void		set_mode(int key, t_data *data);
void		key_up(t_data *data);
void		key_down(t_data *data);
t_d_point	get_first_point(t_probs p, int i, int j);
t_d_point	get_second_point(t_probs p, int i, int j);
void		free_rows(char **row, char *rows);
int			print_key(int key, t_data *data);
int			get_cl(double z, double max);

#endif