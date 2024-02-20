/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:33:20 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/20 18:22:09 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	fdf_scale_init(t_fdf *fdf)
{
	double	scaley;

	fdf->init_scale = fdf->image->width / fdf->map->x_max;
	scaley = fdf->image->height / fdf->map->y_max;
	if (scaley < fdf->init_scale)
		fdf->init_scale = scaley;
	fdf->init_scale *= 0.5;
	fdf->scalediff = fdf->init_scale;
	fdf->scale = 1;
	printf ("init_scale: %f\n", fdf->scalediff);
}

static int	fdf_init(t_fdf *fdf, t_map *map, t_perspective *perspective)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, false);
	if (fdf->mlx == NULL)
		return (EXIT_FAILURE);
	fdf->image = mlx_new_image(fdf->mlx, WIDTH - MENU_WIDTH, HEIGHT);
	if (fdf->image == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(fdf->mlx, fdf->image, MENU_WIDTH, 0) < 0)
		return (EXIT_FAILURE);
	fdf->menu_image = mlx_new_image(fdf->mlx, MENU_WIDTH, HEIGHT);
	if (fdf->menu_image == NULL)
		return (EXIT_FAILURE);
	fdf->map = map;
	fdf->perspective = perspective;
	fdf_scale_init(fdf);
	fdf->x_offset = fdf->image->width / 2;
	fdf->y_offset = fdf->image->height / 2;
	printf ("x_offset: %f\ny_offset: %f\n", fdf->x_offset, fdf->y_offset);
	fdf->spinlock = false;
	fdf->speed = ROTATION_SPEED;
	return (EXIT_SUCCESS);
}

static void	loop_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx, &keyhook, fdf);
	mlx_scroll_hook(fdf->mlx, &scrollhook, fdf);
	mlx_loop_hook(fdf->mlx, &user_inputs, fdf);
	mlx_loop_hook(fdf->mlx, &map_scale, fdf);
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
	if (fdf_init(&fdf, &map, &perspective) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	menu_draw(&fdf);
	loop_hooks(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	map_free(&map);
	return (EXIT_SUCCESS);
}
