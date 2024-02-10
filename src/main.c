/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/10 20:32:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	fdf_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (fdf->mlx == NULL)
		return (EXIT_FAILURE);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (fdf->image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	loop_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &keyhook, fdf);
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
	map = (t_map)
	{NULL, NULL, argv[1], 0, 0, 0};
	map_read(&map);
	perspective = (t_perspective)
	{ISO_ALPHA, ISO_BETA, ISO_GAMMA};
	fdf = (t_fdf)
	{&map, NULL, NULL, &perspective, SCALE,
		map.x_max / 2, map.y_max / 2, false, 1};
	if (fdf_init(&fdf) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	loop_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	map_free(&map);
	return (EXIT_SUCCESS);
}
