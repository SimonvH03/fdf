/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/07 19:51:54 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t
	map_point_colour(
		t_map	*map,
		t_point	*point)
{
	int	current;
	const int	total_height = map->z_max - map->z_min;
	// const int	relative_height = current - min;

	// if (relative_height == 0 || total_height == 0)
	// 	return (Z_LOW);
	current = point->z;
	if (current < 0)
	{
		if (current > map->z_min * 0.1)
			return (Z_LOW_2);
		else
			return (Z_LOW);
	}
	if (point->y * 2 > map->y_max * (1 - (0.10796460177) * 2))
		return (Z_HIGH);
	if (current < map->z_max * .15)
		return (Z_MID_1);
	if (current < map->z_max * .65)
		return (Z_MID_2);
	else
		return (Z_HIGH);
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
			point->colour = map_point_colour(map, point);
			map->project[y][x].colour = point->colour;
			x++;
		}
		y++;
	}
}
