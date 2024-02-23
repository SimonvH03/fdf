/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/02/23 21:03:06 by svan-hoo         ###   ########.fr       */
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
	while (i < map->y_max && map->original[i])
		free(map->original[i++]);
	free(map->original);
}

// from user_inputs.c function input_presets
void	map_project_reset(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			map->project[y][x] = map->original[y][x];
			x++;
		}
		y++;
	}
}

void	map_find_z_min_max(t_map *map)
{
	int	x;
	int	y;
	int	z_val;

	y = 0;
	map->z_min = 0;
	map->z_max = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			z_val = map->original[y][x].z;
			if (z_val < map->z_min)
				map->z_min = z_val;
			if (z_val > map->z_max)
				map->z_max = z_val;
			x++;
		}
		y++;
	}
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
