/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by simon             #+#    #+#             */
/*   Updated: 2024/03/16 01:25:46 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
	menu_print(
		t_fdf *fdf)
{
	const int	margin = 72;
	const int	line = 24;
	int			x;
	int			y;

	mlx_put_string(fdf->mlx, fdf->map->name, x = margin, y = margin);
	mlx_put_string(fdf->mlx, "TRANSLATION", x, y += margin);
	mlx_put_string(fdf->mlx, "Move:	Arrow Keys", x, y += line);
	mlx_put_string(fdf->mlx, "Reset:	N", x, y += line);
	mlx_put_string(fdf->mlx, "ROTATION", x, y += margin);
	mlx_put_string(fdf->mlx, "Pitch:	W-S", x, y += line);
	mlx_put_string(fdf->mlx, "Yaw:	A-D", x, y += line);
	mlx_put_string(fdf->mlx, "Roll:	Q-E", x, y += line);
	mlx_put_string(fdf->mlx, "PRESETS", x, y += margin);
	mlx_put_string(fdf->mlx, "Isometric:	I", x, y += line);
	mlx_put_string(fdf->mlx, "Spherical:	O", x, y += line);
	mlx_put_string(fdf->mlx, "Parallel:	P", x, y += line);
	mlx_put_string(fdf->mlx, "ZOOM", x, y += margin);
	mlx_put_string(fdf->mlx, "In:	Scroll UP", x, y += line);
	mlx_put_string(fdf->mlx, "Out:	Scroll DOWN", x, y += line);
	mlx_put_string(fdf->mlx, "Reset:	M", x, y += line);
	mlx_put_string(fdf->mlx, "FANCY FEATURES", x, y += margin);
	mlx_put_string(fdf->mlx, "Toggle spin:	SPACEBAR", x, y += line);
}

void
	menu_draw(
		t_fdf *fdf)
{
	draw_background(fdf->menu_image, C_MENU);
	mlx_image_to_window(fdf->mlx, fdf->menu_image, 0, 0);
	menu_print(fdf);
}
