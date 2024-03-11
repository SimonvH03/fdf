/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mods.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:05:51 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/10 23:42:11 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	map_fill_polar(
		void	*param,
		int y,
		int x)
{
	t_map	*map;
	t_point	*point;
	t_point temp;

	map = param;
	point = &map->original[y][x];
	temp = (t_point)
	{(map->shape.longitude * x),
		(map->shape.latitude * y),
		(map->radius + point->z),
		point->colour};
	map->polar[y][x] = (t_point)
	{((temp.z) * cos(temp.x) * sin(temp.y)),
		((temp.z) * sin(temp.x) * sin(temp.y)),
		((temp.z) * cos(temp.y)),
		temp.colour};
}

void
	map_set_polar(
		void	*param,
		const int y,
		const int x)
{
	t_map	*map;

	map = param;
	map->project[y][x] = map->polar[y][x];
}

void
	map_set_original(
		void	*param,
		const int y,
		const int x)
{
	t_map	*map;

	map = param;
	map->project[y][x] = map->original[y][x];
}
