/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 12:42:43 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from map_read.c
int	map_malloc_y(t_map *map)
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

int	map_malloc_x(t_map *map, int y)
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

// from map_read.c
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

uint32_t	map_point_colour(int min, int max, double current)
{
	const int	relative_height = current - min;
	const int	total_height = max - min;
	double		ratio;
	uint32_t	le_colour;

	if (relative_height == 0 || total_height == 0)
		return (Z_LOW);
	ratio = (double)(relative_height / total_height);
	le_colour = (Z_LOW + Z_HIGH) / 2 * ratio;
	return (le_colour);
}

void	map_colour(t_map *map)
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
