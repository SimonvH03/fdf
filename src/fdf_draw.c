/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/10 19:01:26 by svan-hoo         ###   ########.fr       */
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

	x_pixel = point->x * fdf->scale;
	y_pixel = point->y * fdf->scale;
	x_pixel += (fdf->image->width / 2) - fdf->x_origin;
	y_pixel += (fdf->image->height / 2) - fdf->y_origin;
	if (x_pixel < fdf->image->width && y_pixel < fdf->image->height)
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel, C_LINES);
	}
	else
	{
		printf("bounds: %d\tx: %f\n", fdf->image->width, x_pixel);
		printf("bounds: %d\ty: %f\n", fdf->image->height, y_pixel);
		return (-1);
	}
	return (0);
}

void	fdf_draw(void *param)
{
	t_fdf		*fdf;
	t_point		*point;
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
			point = &fdf->map->project[y][x];
			if (fdf_draw_point(fdf, point) < 0)
				return ;
			x++;
		}
		y++;
	}
}
