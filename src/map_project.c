/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:44:02 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 22:03:01 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// angle alpha round x-axis
static void	point_rotate_alpha(t_fdf *fdf, t_point *point)
{
	const double	prev_y = point->y;
	const double	alpha_cos = fdf->precalc.a_cos * fdf->perspective->alpha;
	const double	alpha_sin = fdf->precalc.a_sin * fdf->perspective->alpha;

	point->x = point->x;
	point->y = point->y * alpha_cos + point->z * alpha_sin;
	point->z = prev_y * -alpha_sin + point->z * alpha_cos;
}

// angle beta around y-axis
static void	point_rotate_beta(t_fdf *fdf, t_point *point)
{
	const double	prev_x = point->x;
	const double	beta_cos = fdf->precalc.a_cos * fdf->perspective->beta;
	const double	beta_sin = fdf->precalc.a_sin * fdf->perspective->beta;

	point->x = point->x * beta_cos + point->z * beta_sin;
	point->y = point->y;
	point->z = prev_x * -beta_sin + point->z * beta_cos;
}

// angle gamma around z-axis
static void	point_rotate_gamma(t_fdf *fdf, t_point *point)
{
	const double	prev_x = point->x;
	const double	gamma_cos = fdf->precalc.a_cos * fdf->perspective->gamma;
	const double	gamma_sin = fdf->precalc.a_sin * fdf->perspective->gamma;

	point->x = point->x * gamma_cos + point->y * gamma_sin;
	point->y = prev_x * -gamma_sin + point->y * gamma_cos;
	point->z = point->z;
}

void
	map_scale(
		void	*param)
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
void
	map_project(
		void	*param)
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
				point_rotate_gamma(fdf, point);
			if (fdf->perspective->beta)
				point_rotate_beta(fdf, point);
			if (fdf->perspective->alpha)
				point_rotate_alpha(fdf, point);
			x++;
		}
		y++;
	}
	if (fdf->spinlock == false)
		*(fdf->perspective) = (t_perspective){0, 0, 0};
}
