/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/05 17:34:11 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from fildefer.c function main
void	map_free(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->y_max && map->project[i])
		free(map->project[i++]);
	free(map->project);
	i = 0;
	while (i < map->y_max && map->polar[i])
		free(map->polar[i++]);
	free(map->polar);
	i = 0;
	while (i < map->y_max && map->original[i])
		free(map->original[i++]);
	free(map->original);
}

// from fdf_draw.c, menu_draw.c
void	draw_background(mlx_image_t *image, uint32_t colour)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, x, y, colour);
			x++;
		}
		y++;
	}
}
