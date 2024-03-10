/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project_optimized.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/03/10 01:21:10 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	point_rotate_precalculated(
		const t_fdf	*fdf,
		t_point		*point)
{
	double			prev_x;
	double			prev_y;
	const double	gamma_sin = fdf->cosin.a_sin * fdf->precalc.gamma;
	const double	beta_sin = fdf->cosin.a_sin * fdf->precalc.beta;
	const double	alpha_sin = fdf->cosin.a_sin * fdf->precalc.alpha;

	if (fdf->precalc.gamma)
	{
		prev_x = point->x;
		point->x = point->x * fdf->cosin.a_cos + point->y * gamma_sin;
		point->y = prev_x * -gamma_sin + point->y * fdf->cosin.a_cos;
	}
	if (fdf->precalc.beta)
	{
		prev_x = point->x;
		point->x = point->x * fdf->cosin.a_cos + point->z * beta_sin;
		point->z = prev_x * -beta_sin + point->z * fdf->cosin.a_cos;
	}
	if (fdf->precalc.alpha)
	{
		prev_y = point->y;
		point->y = point->y * fdf->cosin.a_cos + point->z * alpha_sin;
		point->z = prev_y * -alpha_sin + point->z * fdf->cosin.a_cos;
	}
}

// victim #3: replaced by map_iteration version

// parse map and rotate point[x,y,z] values around [0,0,0] (same as fdf_project)
// this one is for optimization, given the angle of rotation is constant
// cosin holds the calculated values for cos(fdf.speed) and sin(fdf.speed)
// void
// 	fdf_project_optimized(
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
// 			if (fdf->precalc.gamma || fdf->precalc.beta || fdf->precalc.alpha)
// 				point_rotate_precalculated(fdf, point);
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (fdf->spinlock == false)
// 		fdf->precalc = (t_precalc){0, 0, 0};
// }

void
	fdf_project_optimized(
		void	*param,
		const int y,
		const int x)
{
	const t_fdf	*fdf = param;
	t_point		*point;

	point = &fdf->map->project[y][x];
	if (fdf->precalc.gamma || fdf->precalc.beta || fdf->precalc.alpha)
		point_rotate_precalculated(fdf, point);
}
