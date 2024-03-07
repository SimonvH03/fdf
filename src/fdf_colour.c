/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/08 00:03:42 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t
	fdf_earth_colour(
		t_map	*map,
		t_point	*point)
{
	const double	current = point->z;
	const double	z_max = map->z_max;
	const double	total_height = z_max - map->z_min;

	if (current < 0)
		return (C_EARTH_SEA);
	if (point->y * 2 > map->y_max * (1 - (0.10796460177) * 2))
		return (C_EARTH_SNOW);
	if (current < z_max * 0.01)
		return (C_EARTH_SHORE);
	if (current < z_max * .15)
		return (C_EARTH_LAND);
	if (current < z_max * .65)
		return (C_EARTH_MOUNTAIN);
	else
		return (C_EARTH_SNOW);
}

uint32_t
	gradient(
		double ratio,
		uint32_t start,
		uint32_t end)
{
	return (C_WHITE);
}

uint32_t
	fdf_point_colour(
		t_fdf	*fdf,
		t_point	*point)
{
	const int	relative_height = point->z - fdf->map->z_min;
	const int	total_height = fdf->map->z_max - fdf->map->z_min;
	double		ratio;

	ratio = relative_height / total_height;
	if (ratio < 0.5)
		return (gradient(ratio, fdf->palette.low, fdf->palette.mid));
	else
		return (gradient(ratio, fdf->palette.mid, fdf->palette.high));
}

void
	fdf_colour(
		t_fdf	*fdf)
{
	int		x;
	int		y;
	t_point	*point;

	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->original[y][x];
			point->colour = fdf_point_colour(fdf, point);
			fdf->map->project[y][x].colour = point->colour;
			x++;
		}
		y++;
	}
}
