/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:55:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/07 22:15:45 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	ft_background(void *param)
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
	const t_fdf *fdf = param;
	const t_map	*map = fdf->map;
	t_point		*point;
	int			y;
	int			x;
	
	ft_background(fdf->image);
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			point = &fdf->map->content[y][x];
			mlx_put_pixel(fdf->image, point->x, point->y, C_LINES);
			x++;
		}
		y++;
	}
}
