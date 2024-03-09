/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/03/09 23:45:28 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// angle alpha round x-axis
static void
	point_rotate_alpha(
		t_point	*point,
		const double alpha)
{
	const double	prev_y = point->y;

	point->y = point->y * cos(alpha) + point->z * sin(alpha);
	point->z = prev_y * -sin(alpha) + point->z * cos(alpha);
}

// angle beta around y-axis
static void
	point_rotate_beta(
		t_point	*point,
		const double beta)
{
	const double	prev_x = point->x;

	point->x = point->x * cos(beta) + point->z * sin(beta);
	point->z = prev_x * -sin(beta) + point->z * cos(beta);
}

// angle gamma around z-axis
static void
	point_rotate_gamma(
		t_point	*point,
		const double gamma)
{
	const double	prev_x = point->x;

	point->x = point->x * cos(gamma) + point->y * sin(gamma);
	point->y = prev_x * -sin(gamma) + point->y * cos(gamma);
}

// victim #4: replaced by map_iteration version

// parse map and rotate point[x,y,z] values around [0,0,0]
// this function is only for variable angles
// void
// 	fdf_project(
// 		t_fdf	*fdf)
// {
// 	t_point	*point;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	while (y < fdf->map->y_max)
// 	{
// 		x = 0;
// 		while (x < fdf->map->x_max)
// 		{
// 			point = &fdf->map->project[y][x];
// 			if (fdf->perspective.gamma)
// 				point_rotate_gamma(point, fdf->perspective.gamma);
// 			if (fdf->perspective.beta)
// 				point_rotate_beta(point, fdf->perspective.beta);
// 			if (fdf->perspective.alpha)
// 				point_rotate_alpha(point, fdf->perspective.alpha);
// 			x++;
// 		}
// 		y++;
// 	}
// 	fdf->perspective = (t_perspective){0, 0, 0};
// }

void
	fdf_project(
		const void	*param,
		int y,
		int x)
{
	const t_fdf	*fdf = param;
	t_point		*point;

	point = &fdf->map->project[y][x];
	if (fdf->perspective.gamma)
		point_rotate_gamma(point, fdf->perspective.gamma);
	if (fdf->perspective.beta)
		point_rotate_beta(point, fdf->perspective.beta);
	if (fdf->perspective.alpha)
		point_rotate_alpha(point, fdf->perspective.alpha);
}
