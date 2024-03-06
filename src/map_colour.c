/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 21:16:07 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t
	map_point_colour(
		int min,
		int max,
		int current)
{
	const int	relative_height = current - min;
	const int	total_height = max - min;
	double		ratio;

	if (relative_height == 0 || total_height == 0)
		return (Z_LOW);
	if (current >= max * .8)
		return (Z_HIGH);
	else
		return (Z_MID);
}

void
	map_colour(
		t_map	*map)
{
	int		x;
	int		y;
	t_point	*point;

	y = 0;
	map_find_z_min_max(map);
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			point = &map->original[y][x];
			point->colour = map_point_colour(map->z_min, map->z_max, point->z);
			map->project[y][x].colour = point->colour;
			x++;
		}
		y++;
	}
}
