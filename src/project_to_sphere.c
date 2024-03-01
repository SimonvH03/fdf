/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_to_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:05:51 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/03/01 18:31:15 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/fdf.h"

// y coordinate in point 0,0 will be z value (+ radius)
// x coordinate in point 0,0 will be 0
// y coordinate at angle will be --- of longitude + --- of latitude
// x coordinate at angle will be --- of longitude + --- of latitude
static void	grid_to_sphere(t_point *point, int x, int y)
{
	printf("(%d,%d)\n", x, y);
	
}

void	map_sphere(t_fdf *fdf)
{
	t_point		*point;
	int			y;
	int			x;
	const int	x_max = fdf->map->x_max;
	const int	y_max = fdf->map->y_max;
	const int	radius = fdf->map->radius;
	double		longitude;
	double		latitude;

	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			point = &fdf->map->project[y][x];
			grid_to_sphere(point, x, y);
			x++;
		}
		y++;
	}
	// fdf->ballin = true;
}
