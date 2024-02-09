/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/09 14:26:45 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_background(void *param)
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

void	fdf_draw(void *param)
{
	const t_fdf	*fdf = param;
	t_point		*point;
	int			y;
	int			x;

	ft_background(fdf->image);
	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->content[y][x];
			mlx_put_pixel(fdf->image,
				(point->x * 10) + (WIDTH / 2), (point->y * 10) + (HEIGHT / 2),
				C_LINES);
			x++;
		}
		y++;
	}
}
