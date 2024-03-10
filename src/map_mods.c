/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mods.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:05:51 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/10 01:16:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// victim #7: replaced by map_iteration version

// parse original map and fill map->polar
// void
// 	map_fill_polar(
// 		t_map	*map)
// {
// 	int				y;
// 	int				x;
// 	t_point			*point;
// 	const double	longitude_incr = -2 * PI / (map->x_max);
// 	const double	latitude_in = PI / (map->y_max - 1);

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			point = &map->original[y][x];
// 			map->polar[y][x] = (t_point)
// 			{(longitude_incr * x),
// 				(latitude_in * y),
// 				(map->radius + point->z),
// 				point->colour};
// 			x++;
// 		}
// 		y++;
// 	}
// }

void
	map_fill_polar(
		void	*param,
		int y,
		int x)
{
	t_map			*map;
	const t_point	*point = &map->original[y][x];

	map = param;
	map->polar[y][x] = (t_point)
	{(map->sphere->longitude * x),
		(map->sphere->latitude * y),
		(map->radius + point->z),
		point->colour};
}

// victim #8: replaced by map_iteration version

// convert polar coordinates back to cartesian
// polar is t_point with {(x) beta angle, (y) gamma angle, (z) length}
// swap polar->y and polar->x for x= and y= for cool projection
// void
// 	map_set_polar(
// 		t_map	*map)
// {
// 	int			y;
// 	int			x;
// 	t_point		*polar;

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			polar = &map->polar[y][x];
// 			map->project[y][x] = (t_point)
// 			{((polar->z) * cos(polar->x) * sin(polar->y)),
// 				((polar->z) * sin(polar->x) * sin(polar->y)),
// 				((polar->z) * cos(polar->y)),
// 				polar->colour};
// 			x++;
// 		}
// 		y++;
// 	}
// }

void
	map_set_polar(
		void	*param,
		int y,
		int x)
{
	t_map			*map;
	const t_point	*polar = &map->original[y][x];

	map = param;
	map->project[y][x] = (t_point)
	{((polar->z) * cos(polar->x) * sin(polar->y)),
		((polar->z) * sin(polar->x) * sin(polar->y)),
		((polar->z) * cos(polar->y)),
		polar->colour};
}

// victim #6: replaced by map_iteration version

// from user_inputs.c function input_presets
// void
// 	map_set_original(
// 		t_map	*map)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			map->project[y][x] = map->original[y][x];
// 			x++;
// 		}
// 		y++;
// 	}
// }

void
	map_set_original(
		void	*param,
		int y,
		int x)
{
	t_map	*map;

	map = param;
	map->project[y][x] = map->original[y][x];
}
