/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/03/01 17:05:33 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// angle alpha round x-axis
static void	point_rotate_alpha(t_point *point, double alpha)
{
	double	prev_y;

	prev_y = point->y;
	point->x = point->x;
	point->y = point->y * cos(alpha) + point->z * sin(alpha);
	point->z = prev_y * -sin(alpha) + point->z * cos(alpha);
}

// angle beta around y-axis
static void	point_rotate_beta(t_point *point, double beta)
{
	double	prev_x;

	prev_x = point->x;
	point->x = point->x * cos(beta) + point->z * sin(beta);
	point->y = point->y;
	point->z = prev_x * -sin(beta) + point->z * cos(beta);
}

// angle gamma around z-axis
static void	point_rotate_gamma(t_point *point, double gamma)
{
	double	prev_x;

	prev_x = point->x;
	point->x = point->x * cos(gamma) + point->y * sin(gamma);
	point->y = prev_x * -sin(gamma) + point->y * cos(gamma);
	point->z = point->z;
}

void	map_scale(void *param)
{
	t_fdf	*fdf;
	t_point	*point;
	int		y;
	int		x;

	fdf = param;
	y = 0;
	if (fdf->scalediff == 1)
		return ;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->project[y][x];
			point->x *= fdf->scalediff;
			point->y *= fdf->scalediff;
			point->z *= fdf->scalediff;
			x++;
		}
		y++;
	}
	fdf->scalediff = 1;
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
			point = &fdf->map->project[y][x];
			if (fdf->perspective->gamma)
				point_rotate_gamma(point, fdf->perspective->gamma);
			if (fdf->perspective->beta)
				point_rotate_beta(point, fdf->perspective->beta);
			if (fdf->perspective->alpha)
				point_rotate_alpha(point, fdf->perspective->alpha);
			x++;
		}
		y++;
	}
	if (fdf->spinlock == false)
		*(fdf->perspective) = (t_perspective){0, 0, 0};
}
