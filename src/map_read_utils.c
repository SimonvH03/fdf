/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/04/18 20:13:00 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	map_free_err_sub(
		t_point **point_map
	)
{
	int	i;

	i = 0;
	while (point_map[i] != NULL)
	{
		free(point_map[i]);
		i++;
	}
	free(point_map);
}

int
	map_free_err(
		t_map *map
	)
{
	if (map->original != NULL)
		map_free_err_sub(map->original);
	if (map->project != NULL)
		map_free_err_sub(map->project);
	if (map->polar != NULL)
		map_free_err_sub(map->polar);
	ft_printf("malloc failed\n");
	return (EXIT_FAILURE);
}

// used by map_read()
int
	map_malloc_y(
		t_map *map
	)
{
	map->original = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->original == NULL)
		return (EXIT_FAILURE);
	map->original[0] = NULL;
	map->project = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->project == NULL)
		return (EXIT_FAILURE);
	map->project[0] = NULL;
	map->polar = (t_point **)malloc((map->y_max) * sizeof(t_point *));
	if (map->polar == NULL)
		return (EXIT_FAILURE);
	map->polar[0] = NULL;
	return (EXIT_SUCCESS);
}

// used by map_read()
int
	map_malloc_x(
		t_map *map,
		const int y
	)
{
	map->original[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->original[y] == NULL)
		return (EXIT_FAILURE);
	map->project[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (map->project[y] == NULL)
		return (EXIT_FAILURE);
	map->polar[y] = (t_point *)malloc((map->x_max) * sizeof(t_point));
	if (y == 5) // IF
		map->polar[y] = NULL; // intentional fail
	if (map->polar[y] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
// conditional jump relies on uninitialised values:
// the t_point pointers allocated in map_malloc_x are not terminated
// previously this was resolved by freeing everything at first error
// this is complicated with multiple maps, though
// so is terminating the 'strings' of points...