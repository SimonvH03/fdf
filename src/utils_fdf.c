/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:59:22 by simon             #+#    #+#             */
/*   Updated: 2024/03/06 23:48:38 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void
	fdf_scale_and_project(
		void	*param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->perspective.reproject)
		fdf_project(fdf);
	if (fdf->precalc.reproject)
		fdf_project_optimized(fdf);
	if (fdf->scalediff != 1)
		fdf_scale(fdf);
}

void
	fdf_recenter(
		t_fdf	*fdf)
{
	fdf->x_offset = fdf->image->width / 2;
	fdf->y_offset = fdf->image->height / 2;
}

void
	fdf_scale(
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
			point->x *= fdf->scalediff;
			point->y *= fdf->scalediff;
			point->z *= fdf->scalediff;
			x++;
		}
		y++;
	}
	fdf->scalediff = 1;
}
