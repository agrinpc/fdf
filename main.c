/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:39:37 by miahmadi          #+#    #+#             */
/*   Updated: 2022/11/07 02:48:20 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int	render(t_data *img)
{
	t_probs	probs;

	probs = *(img->prob);
	if (probs.state == 1)
	{
		clear_img(img);
		draw_center(img);
		draw_lines(probs, img);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
		print_mode(img);
		print_data(img);
	}
	return (0);
}

int	main(int argc, char **argv )
{
	t_data			img;
	t_probs			probs;

	if (argc < 1 && argv[0])
		return (0);
	probs = get_data(argv[1]);
	log_data(probs);
	img.mlx = mlx_init();
	img.prob = &probs;
	img.mlx_win = mlx_new_window(img.mlx, WD, HG, "Milad");
	img.img = mlx_new_image(img.mlx, WD, HG);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	mlx_hook(img.mlx_win, 17, 0, closing, &img);
	mlx_hook(img.mlx_win, 2, 0, print_key, &img);
	mlx_loop_hook(img.mlx, render, &img);
	mlx_loop(img.mlx);
}
