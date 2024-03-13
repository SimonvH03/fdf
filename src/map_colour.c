/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/13 19:43:55 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t
	gradient(
		const double ratio,
		const uint32_t start,
		const uint32_t end)
{
	const t_colour_construct	c0 = (t_colour_construct)
	{(start >> 24) & 0xFF,
		(start >> 16) & 0xFF,
		(start >> 8) & 0xFF,
		start & 0xFF};
	const t_colour_construct	c1 = (t_colour_construct)
	{(end >> 24) & 0xFF,
		(end >> 16) & 0xFF,
		(end >> 8) & 0xFF,
		end & 0xFF};
	const t_colour_construct	res = (t_colour_construct)
	{(unsigned int)(c1.r * ratio) + (c0.r * (1 - ratio)),
		(unsigned int)(c1.g * ratio) + (c0.g * (1 - ratio)),
		(unsigned int)(c1.b * ratio) + (c0.b * (1 - ratio)),
		(unsigned int)(c1.a * ratio) + (c0.a * (1 - ratio))};

	return ((uint32_t)((res.r << 24) | (res.g << 16) | (res.b << 8) | res.a));
}

uint32_t
	line_colour(
		const t_line	*line)
{
	double	relative_height;
	double	total_height;
	double	ratio;

	if (line->d_ctl > line->d_pas)
	{
		total_height = line->d_ctl;
		relative_height = line->i;
	}
	else
	{
		total_height = line->d_pas;
		relative_height = line->j;
	}
	if (relative_height == 0 || total_height == 0)
		return (line->p0->colour);
	ratio = relative_height / total_height;
	return (gradient(ratio, line->p0->colour, line->p1->colour));
}

uint32_t
	map_earth_colour(
		const t_map 	*map,
		const t_point	*point)
{
	const double	current_z = point->z;

	if (current_z < 0)
		return (gradient(current_z / map->z_min,
				C_EARTH_SEA, C_EARTH_DEEP_SEA));
	if (point->y > map->y_max * 0.39203539823)
		return (C_EARTH_SNOW);
	if (current_z < (map->z_max * 0.65))
		return (gradient(current_z / (map->z_max * 0.65),
				C_EARTH_LAND, C_EARTH_MOUNTAIN));
	else
		return (gradient(current_z / map->z_max,
				C_EARTH_MOUNTAIN, C_EARTH_SNOW));
}

uint32_t
	map_point_colour(
		const t_map 	*map,
		const t_point	*point)
{
	const double	relative_height = point->z - map->z_min;
	double			ratio;

	if (map->total_height == 0)
		return (map->palette.low);
	ratio = relative_height / map->total_height;
	if (ratio <= 0.5)
		return (gradient(ratio * 2, map->palette.low, map->palette.mid));
	else
		return (gradient(ratio * 2, map->palette.mid, map->palette.high));
}

void
	map_colour(
		void	*param,
		const int y,
		const int x)
{
	t_map	*map;
	t_point	*point;

	map = param;
	point = &map->original[y][x];
	if (map->palette.nr == P_EARTH_NR)
		point->colour = map_earth_colour(map, point);
	else
		point->colour = map_point_colour(map, point);
	map->project[y][x].colour = point->colour;
	map->polar[y][x].colour = point->colour;
}
