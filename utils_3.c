/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:40:56 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:43:32 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

char	*get_str(int map)
{
	char	*res;
	char	*cur;

	cur = get_next_line(map);
	res = malloc(1);
	res[0] = 0;
	while (cur)
	{
		res = ft_strjoin_1(res, cur);
		free(cur);
		cur = get_next_line(map);
	}
	free(cur);
	return (res);
}

int	get_cl(double z, double max)
{
	double	c;

	c = z / max;
	if (c <= 0.125)
		return (0x00caf0f8);
	if (c <= 0.25)
		return (0x00ade8f4);
	if (c <= 0.375)
		return (0x0090e0ef);
	if (c <= 0.5)
		return (0x0048cae4);
	if (c <= 0.625)
		return (0x0000b4d8);
	if (c <= 0.75)
		return (0x000096c7);
	if (c <= 0.875)
		return (0x000077b6);
	if (c <= 1)
		return (0x00023e8a);
	return (0x00caf0f8);
}

void	log_data(t_probs prob)
{
	int	i;
	int	j;

	i = -1;
	while (++i < prob.h)
	{
		j = -1;
		while (++j < prob.w)
			ft_printf("%2d ", prob.d[i][j]);
		ft_printf("\n");
	}
}

void	print_points(t_probs prob, t_data *data)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = -1;
	while (++i < prob.h)
	{
		j = -1;
		while (++j < prob.w)
		{
			x = MG + (j * prob.xl);
			y = MG + (i * prob.yl);
			my_mlx_pixel_put(data, x, y, 0x006a994e);
		}
	}
}

void	print_mode(t_data *data)
{
	t_probs	prob;

	prob = *(data->prob);
	mlx_string_put(data->mlx, data->mlx_win, 30, 20, 0x00ffba08, "Mode: ");
	if (prob.mode == 0)
		mlx_string_put(data->mlx, data->mlx_win, 90, 20, 0x00efefef, "Pan");
	if (prob.mode == 1)
		mlx_string_put(data->mlx, data->mlx_win, 90,
			20, 0x00efefef, "Rotate X");
	if (prob.mode == 2)
		mlx_string_put(data->mlx, data->mlx_win, 90,
			20, 0x00efefef, "Rotate Y");
	if (prob.mode == 3)
		mlx_string_put(data->mlx, data->mlx_win, 90,
			20, 0x00efefef, "Rotate Z");
	if (prob.mode == 4)
		mlx_string_put(data->mlx, data->mlx_win, 90, 20, 0x00efefef, "Zoom");
	if (prob.mode == 5)
		mlx_string_put(data->mlx, data->mlx_win, 90, 20, 0x00efefef, "Z Scale");
}
