/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 02:40:52 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:43:08 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	get_height(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i])
		if (str[i] == '\n')
			res++;
	return (res);
}

int	get_width(char *str)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] == ' ')
		{
			res++;
			while (str[++i] && str[i] == ' ')
				;
			i--;
		}
	}
	if (i > 0)
		res++;
	return (res);
}

void	free_rows(char **row, char *rows)
{
	free(rows);
	free(row);
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
	while (++i < h)
		data[i] = malloc(w * sizeof(int));
	i = -1;
	while (++i < h && rows[i])
	{
		row = ft_split(rows[i], ' ');
		j = -1;
		while (++j < w && row[j])
		{
			data[i][j] = ft_atoi(row[j]);
			free(row[j]);
		}
		free_rows(row, rows[i]);
	}
	free(rows);
	return (data);
}

int	get_max_z(int **numbers, int w, int h)
{
	int	i;
	int	j;
	int	max;

	i = -1;
	max = numbers[0][0];
	while (++i < h)
	{
		j = -1;
		while (++j < w)
			if (max < numbers[i][j])
				max = numbers[i][j];
	}
	return (max);
}
