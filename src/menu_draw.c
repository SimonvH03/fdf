/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by simon             #+#    #+#             */
/*   Updated: 2024/03/16 18:40:28 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
	menu_print_2(
		t_fdf *fdf,
		int x,
		int y)
{
	const int	margin = 48;
	const int	line = 24;
	const int	tab = 144;

	mlx_put_string(fdf->mlx, "ROTATION", x, y += margin);
	mlx_put_string(fdf->mlx, "Pitch:", x, y += line);
	mlx_put_string(fdf->mlx, "W - S", x + tab, y);
	mlx_put_string(fdf->mlx, "Yaw:", x, y += line);
	mlx_put_string(fdf->mlx, "A - D", x + tab, y);
	mlx_put_string(fdf->mlx, "Roll:", x, y += line);
	mlx_put_string(fdf->mlx, "Q - E", x + tab, y);
	mlx_put_string(fdf->mlx, "Zoom:", x, y += margin);
	mlx_put_string(fdf->mlx, "Scroll UP - DOWN", x + tab, y);
	mlx_put_string(fdf->mlx, "Spinlock:", x, y += line);
	mlx_put_string(fdf->mlx, "SPACEBAR", x + tab, y);
	mlx_put_string(fdf->mlx, "Colour cycle:", x, y += line);
	mlx_put_string(fdf->mlx, "C", x + tab, y);
	mlx_put_string(fdf->mlx, "Reset:", x, y += line);
	mlx_put_string(fdf->mlx, "R", x + tab, y);
}

static void
	menu_print_1(
		t_fdf *fdf)
{
	const int	margin = 48;
	const int	line = 24;
	const int	tab = 144;
	int			x;
	int			y;

	mlx_put_string(fdf->mlx, fdf->map->name, x = margin, y = margin);
	mlx_put_string(fdf->mlx, "PRESETS", x, y += margin);
	mlx_put_string(fdf->mlx, "Parallel", x, y += line);
	mlx_put_string(fdf->mlx, "P", x + tab, y);
	mlx_put_string(fdf->mlx, "Isometric", x, y += line);
	mlx_put_string(fdf->mlx, "I", x + tab, y);
	mlx_put_string(fdf->mlx, "Globe", x, y += line);
	mlx_put_string(fdf->mlx, "O", x + tab, y);
	mlx_put_string(fdf->mlx, "Radar", x, y += line);
	mlx_put_string(fdf->mlx, "U", x + tab, y);
	mlx_put_string(fdf->mlx, "TRANSLATION", x, y += margin);
	mlx_put_string(fdf->mlx, "Move:", x, y += line);
	mlx_put_string(fdf->mlx, "Arrow Keys", x + tab, y);
	mlx_put_string(fdf->mlx, "Switch Mode:", x, y += line);
	mlx_put_string(fdf->mlx, "T", x + tab, y);
	menu_print_2(fdf, x, y);
}

void
	menu_draw(
		t_fdf *fdf)
{
	draw_background(fdf->menu_image, C_MENU);
	mlx_image_to_window(fdf->mlx, fdf->menu_image, 0, 0);
	menu_print_1(fdf);
}
