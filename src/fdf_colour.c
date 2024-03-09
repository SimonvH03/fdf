/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/09 17:16:49 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

uint32_t
	fdf_earth_colour(
		t_fdf	*fdf,
		t_point	*point)
{
	const double	current = point->z;
	const double	z_max = fdf->map->z_max;
	const double	total_height = z_max - fdf->map->z_min;

	if (current < 0)
		return (C_EARTH_SEA);
	if (point->y * 2 > fdf->map->y_max * (1 - (0.10796460177) * 2))
		return (C_EARTH_SNOW);
	if (current < z_max * 0.01)
		return (C_EARTH_SHORE);
	if (current < z_max * .15)
		return (C_EARTH_LAND);
	if (current < z_max * .65)
		return (C_EARTH_MOUNTAIN);
	else
		return (C_EARTH_SNOW);
}

uint32_t
	gradient(
		double ratio,
		uint32_t start,
		uint32_t end)
{
	const t_colour_construct	c0 = (t_colour_construct)
	{(start >> 24) & 0xFF,
	(start >> 16) & 0xFF,
	(start >> 8) & 0xFF,
	start & 0xFF};
	// printf("C0: %d, %d, %d, %d\n", c0.r, c0.g, c0.b, c0.a);
	const t_colour_construct	c1 = (t_colour_construct)
	{(end >> 24) & 0xFF,
	(end >> 16) & 0xFF,
	(end >> 8) & 0xFF,
	end & 0xFF};
	// printf("C1: %d, %d, %d, %d\n", c1.r, c1.g, c1.b, c1.a);
	const t_colour_construct	res = (t_colour_construct)
	{(unsigned int)(c1.r * ratio) + (c0.r * (1 - ratio)),
	(unsigned int)(c1.g * ratio) + (c0.g * (1 - ratio)),
	(unsigned int)(c1.b * ratio) + (c0.b * (1 - ratio)),
	(unsigned int)(c1.a * ratio) + (c0.a * (1 - ratio))};
	// printf("RE: %d, %d, %d, %d\nRATIO: %f\n", res.r, res.g, res.b, res.a, ratio);
	return ((uint32_t)((res.r << 24) | (res.g << 16) | (res.b << 8) | res.a));
}

uint32_t
	fdf_point_colour(
		t_fdf	*fdf,
		t_point	*point)
{
	const double	relative_height = point->z - fdf->map->z_min;
	const double	total_height = fdf->map->z_max - fdf->map->z_min;
	double			ratio;

	ratio = relative_height / total_height;
	// printf("ratio: %f\n", ratio);
	if (ratio <= 0.5)
		return (gradient(ratio * 2, fdf->palette.low, fdf->palette.mid));
	else
		return (gradient(ratio * 2, fdf->palette.mid, fdf->palette.high));
}

uint32_t
	fdf_line_colour(
		t_fdf	*fdf,
		t_line	*line)
{
	double	relative_height;
	double	total_height;
	double	ratio;

	if (line->d_ctl > line->d_pas)
	{
		total_height = line->d_ctl;
		relative_height = line->i;
	}
	else
	{
		total_height = line->d_pas;
		relative_height = line->i;
	}
	ratio = relative_height / total_height;
	// printf("r: %f\ti: %d\td:%d\n", ratio, line->i, line->d_ctl);
	return (gradient(ratio, line->p0->colour, line->p1->colour));
}

void
	fdf_colour(
		t_fdf	*fdf)
{
	int		x;
	int		y;
	t_point	*point;

	y = 0;
	while (y < fdf->map->y_max)
	{
		x = 0;
		while (x < fdf->map->x_max)
		{
			point = &fdf->map->original[y][x];
			point->colour = fdf_earth_colour(fdf, point);
			fdf->map->project[y][x].colour = point->colour;
			x++;
		}
		y++;
	}
}
