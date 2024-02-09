/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/09 19:05:40 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	loop_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &user_inputs, fdf);
	mlx_loop_hook(fdf->mlx, &map_project, fdf);
	mlx_loop_hook(fdf->mlx, &fdf_draw, fdf);
}

int	main(int argc, char **argv)
{
	t_map			map;
	t_perspective	perspective;
	t_fdf			fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	// init then read map
	map = (t_map){NULL, 0, argv[1], 0, 0};
	map_read(&map);
	perspective = (t_perspective){ALPHA, BETA, GAMMA};
	fdf.map = &map;
	fdf.perspective = &perspective;
	fdf.x_origin = map.x_max / 2;
	fdf.y_origin = map.y_max / 2;
	fdf.scale = SCALE;
	fdf.mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (fdf.mlx == NULL)
		return (EXIT_FAILURE);
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (fdf.image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(fdf.mlx, fdf.image, 0, 0) < 0)
		return (EXIT_FAILURE);
	loop_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	map_free(&map);
	return (EXIT_SUCCESS);
}
