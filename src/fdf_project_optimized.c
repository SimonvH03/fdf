/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project_optimized.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 23:42:51 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// angle alpha round x-axis
static void	point_rotate_alpha(t_fdf *fdf, t_point *point)
{
	const double	prev_y = point->y;
	const double	alpha_cos = fdf->cosin.a_cos;
	const double	alpha_sin = fdf->cosin.a_sin * fdf->precalc.alpha;

	point->x = point->x;
	point->y = point->y * alpha_cos + point->z * alpha_sin;
	point->z = prev_y * -alpha_sin + point->z * alpha_cos;
}

// angle beta around y-axis
static void	point_rotate_beta(t_fdf *fdf, t_point *point)
{
	const double	prev_x = point->x;
	const double	beta_cos = fdf->cosin.a_cos;
	const double	beta_sin = fdf->cosin.a_sin * fdf->precalc.beta;

	point->x = point->x * beta_cos + point->z * beta_sin;
	point->y = point->y;
	point->z = prev_x * -beta_sin + point->z * beta_cos;
}

// angle gamma around z-axis
static void	point_rotate_gamma(t_fdf *fdf, t_point *point)
{
	const double	prev_x = point->x;
	const double	gamma_cos = fdf->cosin.a_cos;
	const double	gamma_sin = fdf->cosin.a_sin * fdf->precalc.gamma;

	point->x = point->x * gamma_cos + point->y * gamma_sin;
	point->y = prev_x * -gamma_sin + point->y * gamma_cos;
	point->z = point->z;
}

// parse map and rotate point[x,y,z] values around [0,0,0] (same as fdf_project)
// this one is for optimization, given the angle of rotation is constant
// cosin holds the calculated values for cos(fdf.speed) and sin(fdf.speed)
void
	fdf_project_optimized(
		t_fdf	*fdf)
{
	t_point	*point;
	int		y;
	int		x;

	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->project[y][x];
			if (fdf->precalc.gamma)
				point_rotate_gamma(fdf, point);
			if (fdf->precalc.beta)
				point_rotate_beta(fdf, point);
			if (fdf->precalc.alpha)
				point_rotate_alpha(fdf, point);
			x++;
		}
		y++;
	}
	if (fdf->spinlock == false)
		fdf->precalc = (t_precalc){0, 0, 0};
}
