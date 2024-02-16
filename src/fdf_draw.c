/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/16 17:40:29 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	fdf_draw_point(t_fdf *fdf, t_point point)
{
	double	x_pixel;
	double	y_pixel;

	x_pixel = point.x + (fdf->image->width / 2);
	y_pixel = point.y + (fdf->image->height / 2);
	if (x_pixel < fdf->image->width && y_pixel < fdf->image->height
		&& x_pixel > 0 && y_pixel > 0)
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel, 0x00FFFFFF);
	}
	else
	{
		// printf("bounds: %d\tx: %f\n", fdf->image->width, x_pixel);
		// printf("bounds: %d\ty: %f\n", fdf->image->height, y_pixel);
		return (-1);
	}
	return (0);
}

// static double	fdf_draw_line(t_fdf *fdf, t_point point1, t_point point2)
// {
	
// }

void	fdf_draw(void *param)
{
	t_fdf	*fdf;
	int		y;
	int		x;

	fdf = param;
	draw_background(fdf->image, C_BACKGROUND);
	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			// if ((x + 1) < fdf->map->x_max)
			// 	fdf_draw_line(fdf, fdf->map->project[y][x], fdf->map->project[y][x + 1]);
			// if ((y + 1) < fdf->map->y_max)
			// 	fdf_draw_line(fdf, fdf->map->project[y][x], fdf->map->project[y + 1][x]);
			fdf_draw_point(fdf, fdf->map->project[y][x]);
			x++;
		}
		y++;
	}
}
