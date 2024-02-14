/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/14 16:43:24 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	fdf_background(void *param)
{
	mlx_image_t	*image;
	uint32_t	x;
	uint32_t	y;

	image = param;
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, C_BACKGROUND);
			x++;
		}
		y++;
	}
}

int	fdf_draw_point(t_fdf *fdf, t_point *point)
{
	double	x_pixel;
	double	y_pixel;

	x_pixel = point->x + (fdf->image->width / 2);
	y_pixel = point->y + (fdf->image->height / 2);
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

void	fdf_draw_line(t_fdf *fdf, t_point *point1, t_point *point2)
{
}

void	fdf_draw(void *param)
{
	t_fdf		*fdf;
	t_point		*point1;
	int			y;
	int			x;

	fdf = param;
	fdf_background(fdf->image);
	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point1 = &fdf->map->project[y][x];
			if ((x + 1) < fdf->map->x_max)
				fdf_draw_line(fdf, point1, &fdf->map->project[y][x + 1]);
			if ((y + 1) < fdf->map->y_max)
				fdf_draw_line(fdf, point1, &fdf->map->project[y + 1][x]);
			fdf_draw_point(fdf, point1);
			x++;
		}
		y++;
	}
}
