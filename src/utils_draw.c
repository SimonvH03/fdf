/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/13 15:48:56 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// from fdf_draw.c, menu_draw.c
void
	draw_background(
		const mlx_image_t	*image,
		const uint32_t		colour)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	while (j < image->height)
	{
		i = 0;
		while (i < image->width)
		{
			mlx_put_pixel((mlx_image_t *)image, i, j, colour);
			i++;
		}
		j++;
	}
}

int
	horizon_pythagoras(const t_fdf *fdf, const t_point *point)
{
	if ((point->x * point->x) + (point->y * point->y) <
		(fdf->darksquare * fdf->darksquare * 2) * fdf->scale.total * fdf->scale.total)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

// if the line crosses the horizon (p0 ^ p1) we substitute it's
// inlying point with the crossing point.
// this is calculated by taking the distance of either point in respect to the radius
// then this ratio is used to traverse the line and find the subtitute point
int
	substitute_point(const t_fdf *fdf, t_line *line)
{
	t_point	*substitute;
	int		p0_check;
	int		p1_check;

	p0_check = horizon_pythagoras(fdf, line->p0);
	p1_check = horizon_pythagoras(fdf, line->p1);
	if (!(p0_check && p1_check))
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int
darksquare(
	const t_fdf		*fdf,
	const t_point	*point)
{
	if (ft_abs(point->x) < fdf->darksquare * fdf->scale.total
		&& ft_abs(point->y) < fdf->darksquare * fdf->scale.total)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

// first we need a margin, don't calculate if x or y is within 'dark square';
//;dark square has half side lengths equal to radius / sqrt(2)
// then we use pythagoras' theorum to see if x,y falls within the horizon
// cases:
// if both points are over the horizon; return (1)
// if both points are outside the horizon; return (0)
// if only one point is over the horizon;
//;malloc a new point (with colour) exactly on the horizon and return (0)
int
	over_the_horizon(
		const t_fdf	*fdf,
		t_line		*line)
{
	if (fdf->ballin == false)
		return (EXIT_SUCCESS);
	if (1 || (line->p0->z < 0.1 && line->p1->z < 0.1))
	{
		if (darksquare(fdf, line->p0) || darksquare(fdf, line->p1))
			return (EXIT_FAILURE);
		if (substitute_point(fdf, line))
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
