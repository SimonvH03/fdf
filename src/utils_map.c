/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/09 21:51:43 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from map_read.c
int
	map_malloc_y(
		t_map	*map)
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
		t_map	*map,
		int y)
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

// victim #9: replaced by map_iteration version

// from map_read.c
// void
// 	map_find_z_min_max(
// 		t_map	*map)
// {
// 	int	x;
// 	int	y;
// 	int	z_val;

// 	y = 0;
// 	map->z_min = 0;
// 	map->z_max = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			z_val = map->original[y][x].z;
// 			if (z_val < map->z_min)
// 				map->z_min = z_val;
// 			if (z_val > map->z_max)
// 				map->z_max = z_val;
// 			x++;
// 		}
// 		y++;
// 	}
// 	map->radius = (map->z_max - map->z_min) * 10;
// }

void
	map_find_z_min_max(
		void	*param,
		int y,
		int x)
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

// from main.c
void
	map_free(
		t_map	*map)
{
	int	i;

	i = 0;
	while (i < map->y_max && map->project[i])
		free(map->project[i++]);
	free(map->project);
	i = 0;
	while (i < map->y_max && map->polar[i])
		free(map->polar[i++]);
	free(map->polar);
	i = 0;
	while (i < map->y_max && map->original[i])
		free(map->original[i++]);
	free(map->original);
}
