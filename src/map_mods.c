/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mods.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:05:51 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/05 19:04:02 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// parse original map and fill map->polar
void	map_fill_polar(t_map *map)
{
	int				y;
	int				x;
	t_point			*point;
	const double	longitude_incr = 2 * PI / (map->x_max);
	const double	latitude_in = PI / (map->y_max - 1);

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			point = &map->original[y][x];
			map->polar[y][x] = (t_point)
			{(longitude_incr * point->x),
				(latitude_in * point->y),
				(map->radius + point->z)};
			x++;
		}
		y++;
	}
}

// convert polar coordinates back to cartesian
// polar is t_point with {(x) beta angle, (y) gamma angle, (z) length}
void	map_set_polar(t_map *map)
{
	int			y;
	int			x;
	t_point		*polar;
	const int	r = map->radius;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			polar = &map->polar[y][x];
			map->project[y][x] = (t_point)
			{(r * cos(polar->x) * sin(polar->y)),
				(r * sin(polar->x) * sin(polar->y)),
				(r * cos(polar->y))};
			x++;
		}
		y++;
	}
}

// from user_inputs.c function input_presets
void	map_set_original(t_map *map)
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
