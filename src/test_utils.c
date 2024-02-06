/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/02/06 21:23:27 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	check_map_result_c(t_map *map, const char c)
{
	int		y;
	int		x;

	printf("[%c]\n", c);
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			if (c == 'x')
				printf("%-3d", (map->content[y][x]).x);
			if (c == 'y')
				printf("%-3d", (map->content[y][x]).y);
			if (c == 'z')
				printf("%-3d", (map->content[y][x]).z);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

static void	check_map_result_p(t_map *map)
{
	int		y;
	int		x;
	t_point	*tmpoint;

	printf("[x,y,z]\n");
	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			tmpoint = &map->content[y][x];
			printf("%d,", tmpoint->x);
			printf("%d,", tmpoint->y);
			printf("%d\t", tmpoint->z);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}

void	check_map_result(t_map *map)
{
	check_map_result_c(map, 'x');
	check_map_result_c(map, 'y');
	check_map_result_c(map, 'z');
	check_map_result_p(map);
}
