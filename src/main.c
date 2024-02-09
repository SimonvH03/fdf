/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/09 16:24:00 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	loop_hooks(t_fdf *fdf)
{
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
	// check_map_result(&map, "read", "z");
	// init perspective to test map projection
	perspective = (t_perspective){0.7, 0.2, 0.5};
	// add map and perspective to fdf
	fdf.map = &map;
	fdf.perspective = &perspective;
	fdf.x_origin = map.x_max / 2;
	fdf.y_origin = map.y_max / 2;
	fdf.scale = 20;
	fdf.mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
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
