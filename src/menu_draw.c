/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:50 by simon             #+#    #+#             */
/*   Updated: 2024/02/23 19:44:16 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	menu_print(t_fdf *fdf)
{
	const int	margin = 72;
	const int	line = 24;
	int			x;
	int			y;

	mlx_put_string(fdf->mlx, fdf->map->name, x = margin, y = margin);
	mlx_put_string(fdf->mlx, "Controls", x, y += margin);
	mlx_put_string(fdf->mlx, "Zoom:	scroll UP/DOWN", x, y += line);
	mlx_put_string(fdf->mlx, "Pitch:	W/S", x, y += line);
	mlx_put_string(fdf->mlx, "Yaw:	A/D", x, y += line);
	mlx_put_string(fdf->mlx, "Roll:	Q/E", x, y += line);
	mlx_put_string(fdf->mlx, "Presets", x, y += margin);
	mlx_put_string(fdf->mlx, "Isometric view:	I", x, y += line);
	mlx_put_string(fdf->mlx, "Parallel view:	P", x, y += line);
	mlx_put_string(fdf->mlx, "Other", x, y += margin);
	mlx_put_string(fdf->mlx, "Toggle spin:	SPACEBAR", x, y += line);
	mlx_put_string(fdf->mlx, "Reset zoom:	M", x, y += line);
}

void	menu_draw(t_fdf *fdf)
{
	draw_background(fdf->menu_image, C_MENU);
	mlx_image_to_window(fdf->mlx, fdf->menu_image, 0, 0);
	menu_print(fdf);
}
