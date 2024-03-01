/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_to_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:05:51 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/01 21:15:07 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/fdf.h"

// y coordinate in point 0,0 will be z value (+ radius)
// x coordinate in point 0,0 will be 0
// y coordinate at angle will be --- of longitude + --- of latitude
// x coordinate at angle will be --- of longitude + --- of latitude
static void	grid_to_sphere(t_point *point, double x, double y)
{
	printf("(%f,%f)\n", x, y);
	
}

void	map_sphere(t_fdf *fdf)
{
	t_point		*point;
	int			y;
	int			x;
	const int	x_max = fdf->map->x_max;
	const int	y_max = fdf->map->y_max;
	const int	radius = fdf->map->radius;

	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			point = &fdf->map->project[y][x];
			grid_to_sphere(point, point->x, point->y);
			x++;
		}
		y++;
	}
	// fdf->ballin = true;
}
