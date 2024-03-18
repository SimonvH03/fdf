/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_optimized.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:30:28 by simon             #+#    #+#             */
/*   Updated: 2024/03/18 01:57:30 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void
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

// from project.c / project()
void
	fdf_rotate_optimized(
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
