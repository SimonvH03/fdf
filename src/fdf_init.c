/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:49:26 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/26 21:07:29 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
	fdf_scale_init(
		t_fdf *fdf)
{
	double	scalefinder;

	fdf->scale.initial = (double)fdf->image->width / (double)fdf->map->x_max;
	scalefinder = (double)fdf->image->height / (double)fdf->map->y_max;
	if (scalefinder < fdf->scale.initial)
		fdf->scale.initial = scalefinder;
	if (fdf->map->radius == 0)
		fdf->scale.sphere = 1;
	else
		fdf->scale.sphere = fdf->image->width / (2.2 * fdf->map->radius)
			* DEFAULT_SCALE;
	fdf->scale.initial *= DEFAULT_SCALE;
	if (fdf->scale.initial == 0)
		fdf->scale.initial = 0.1;
	fdf->scale.diff = fdf->scale.initial;
	fdf->scale.total = 1;
}

static int
	fdf_mlx_init(
		t_fdf *fdf)
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
	return (EXIT_SUCCESS);
}

// from main.c / main()
int
	fdf_init(
		t_fdf *fdf,
		t_map *map)
{
	if (fdf_mlx_init(fdf) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fdf->map = map;
	fdf->perspective = (t_perspective){ISO_ALPHA, ISO_BETA, ISO_GAMMA, true};
	fdf->precalc = (t_precalc){0, 0, 0, 1, true};
	fdf->speed = ROTATION_SPEED;
	fdf->cosin = (t_cosin){cos(fdf->speed), sin(fdf->speed)};
	fdf_scale_init(fdf);
	fdf->radius = fdf->map->radius;
	fdf->darksquare = fdf->radius / sqrt(2);
	fdf_center_offset(fdf);
	fdf->spinlock = false;
	fdf->redraw = true;
	fdf->ballin = false;
	fdf->horizon = true;
	return (EXIT_SUCCESS);
}
