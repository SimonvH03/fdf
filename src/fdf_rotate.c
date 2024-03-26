/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/03/26 21:13:47 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// angle gamma around z-axis (roll)
static void
	point_rotate_gamma(
		t_point *point,
		const double gamma)
{
	const double	prev_x = point->x;

	point->x = point->x * cos(gamma) + point->y * sin(gamma);
	point->y = prev_x * -sin(gamma) + point->y * cos(gamma);
}

// angle beta around y-axis (yaw)
static void
	point_rotate_beta(
		t_point *point,
		const double beta)
{
	const double	prev_x = point->x;

	point->x = point->x * cos(beta) + point->z * sin(beta);
	point->z = prev_x * -sin(beta) + point->z * cos(beta);
}

// angle alpha round x-axis (pitch)
static void
	point_rotate_alpha(
		t_point *point,
		const double alpha)
{
	const double	prev_y = point->y;

	point->y = point->y * cos(alpha) + point->z * sin(alpha);
	point->z = prev_y * -sin(alpha) + point->z * cos(alpha);
}

// from project.c / project()
void
	fdf_rotate(
		void *param,
		const int y,
		const int x)
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
