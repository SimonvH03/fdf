/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/16 00:32:47 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int
	map_malloc_y(
		t_map *map)
{
	map->original = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->original == NULL)
		return (EXIT_FAILURE);
	map->project = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->project == NULL)
		return (EXIT_FAILURE);
	map->polar = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->polar == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int
	map_malloc_x(
		t_map *map,
		const int y)
{
	map->original[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->original[y] == NULL)
		return (EXIT_FAILURE);
	map->project[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->project[y] == NULL)
		return (EXIT_FAILURE);
	map->polar[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->polar[y] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void
	map_find_z_min_max(
		void *param,
		const int y,
		const int x)
{			
	t_map	*map;
	int		z_val;

	map = param;
	z_val = map->original[y][x].z;
	if (z_val < map->z_min)
		map->z_min = z_val;
	if (z_val > map->z_max)
		map->z_max = z_val;
}
