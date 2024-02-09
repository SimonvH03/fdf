/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/02/09 20:21:13 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// angle alpha round x-axis
static void	point_rotate_alpha(t_point *point, double alpha)
{
	double	prev_y;

	prev_y = point->y;
	point->y = point->y * cos(alpha) + point->z * sin(alpha);
	point->z = prev_y * -sin(alpha) + point->z * cos(alpha);
}

// angle beta around y-axis
static void	point_rotate_beta(t_point *point, double beta)
{
	double	prev_z;

	prev_z = point->z;
	point->z = point->z * cos(beta) + point->x * sin(beta);
	point->x = prev_z * -sin(beta) + point->x * cos(beta);
}

// angle gamma around z-axis
static void	point_rotate_gamma(t_point *point, double gamma)
{
	double	prev_x;

	prev_x = point->x;
	point->x = point->x * cos(gamma) + point->y * -sin(gamma);
	point->y = prev_x * sin(gamma) + point->y * cos(gamma);
}

// parse map and rotate point[x,y,z] values around [0,0,0]
void	map_project(void *param)
{
	t_fdf	*fdf;
	t_point	*point;
	int		y;
	int		x;

	fdf = param;
	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->content[y][x];
			if (fdf->perspective->gamma)
				point_rotate_gamma(point, -rad(fdf->perspective->gamma));
			if (fdf->perspective->beta)
				point_rotate_beta(point, -rad(fdf->perspective->beta));
			if (fdf->perspective->alpha)
				point_rotate_alpha(point, -rad(fdf->perspective->alpha));
			x++;
		}
		y++;
	}
	*(fdf->perspective) = (t_perspective){0, 0, 0};
}
