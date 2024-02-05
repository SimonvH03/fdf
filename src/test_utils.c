/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:04:03 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/02/05 21:15:14 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	check_map_result(t_map *map)
{
	int		y;
	int		x;
	t_point	*tmpoint;

	y = 0;
	while (y < map->y_max)
	{
		x = 0;
		while (x < map->x_max)
		{
			tmpoint = &map->content[y][x];
			printf("%2d", tmpoint->z);
			x++;
		}
		printf("\n");
		y++;
	}
}
