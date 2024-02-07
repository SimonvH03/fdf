/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/02/07 02:39:28 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// print x, y or z value (based on c) from every t_point in the map
static void	check_map_result_c(t_map *map, const char c)
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
				printf("%3.0f", (map->content[y][x]).x);
			if (c == 'y')
				printf("%3.0f", (map->content[y][x]).y);
			if (c == 'z')
				printf("%3.0f", (map->content[y][x]).z);
			x++;
		}
		printf("\n");
		y++;
	}
}

// static void	check_map_result_p(t_map *map)
// {
// 	int		y;
// 	int		x;
// 	t_point	*tmpoint;

// 	printf("[x,y,z]\n");
// 	y = 0;
// 	while (y < map->y_max)
// 	{
// 		x = 0;
// 		while (x < map->x_max)
// 		{
// 			tmpoint = &map->content[y][x];
// 			printf("%.0f,", tmpoint->x);
// 			printf("%.0f,", tmpoint->y);
// 			printf("%.0f\t", tmpoint->z);
// 			x++;
// 		}
// 		printf("\n");
// 		y++;
// 	}
// 	printf("\n");
// }

// action: the event we are checking the result of
// showing: x, y, or z values
void	check_map_result(t_map *map, const char *str, const char c)
{
	printf("\naction: %s\nshowing: [%c]\n", str, c);
	check_map_result_c(map, c);
	// check_map_result_p(map);
}
