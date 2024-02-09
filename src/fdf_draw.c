/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/09 15:07:52 by simon            ###   ########.fr       */
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

int	fdf_draw_pixel(t_fdf *fdf, t_point *point)
{
	double	x_pixel;
	double	y_pixel;

	printf ("x_pixel = %f + %d - %f\n", point->x, (fdf->image->width / 2), fdf->x_origin);
	x_pixel = point->x + (fdf->image->width / 2) - fdf->x_origin;
	y_pixel = point->y + (fdf->image->height / 2) - fdf->y_origin;
	x_pixel *= 10;
	y_pixel *= 10;
	if (x_pixel < fdf->image->width && y_pixel < fdf->image->height)
	{
		mlx_put_pixel(fdf->image, x_pixel, y_pixel, C_LINES);
	}
	return (0);
}

// scale (point->x,y * scale) is not bound by image or window size yet
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
			point = &fdf->map->content[y][x];
			if (fdf_draw_pixel(fdf, point) < 0)
				return ;
			x++;
		}
		y++;
	}
}
