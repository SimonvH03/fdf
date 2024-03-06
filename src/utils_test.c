/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 18:36:02 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// print x, y or z value (based on c) from every t_point in the map
static void
	check_map_result_c(
		t_map *map,
		const char c)
{
	int		y;
	int		x;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (c == 'x')
				printf("%5.1f", (map->project[y][x]).x);
			if (c == 'y')
				printf("%5.1f", (map->project[y][x]).y);
			if (c == 'z')
				printf("%5.1f", (map->project[y][x]).z);
			x++;
		}
		printf("\n");
		y++;
	}
}

// action: the event we are checking the result of
// showing: x, y, or z values
void
	check_map_result(
		t_map *map,
		const char *str, const char *values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		printf("\naction: %s\nshowing: [%c]\n", str, values[i]);
		check_map_result_c(map, values[i]);
		i++;
	}
}
