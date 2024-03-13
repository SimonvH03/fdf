/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_the_horizon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:26:03 by simon             #+#    #+#             */
/*   Updated: 2024/03/14 00:24:47 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double
	distance_pythagoras(
		const double delta_a,
		const double delta_b)
{
	return (sqrt((delta_a * delta_a) + (delta_b * delta_b)));
}

// cheapest version of horizon check
// returns if point is outside of radius
int
	horizon_pythagoras(
		const t_fdf *fdf,
		const t_point *point)
{
	if ((point->x * point->x) + (point->y * point->y)
		< (fdf->radius * fdf->radius))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// if the line crosses the horizon (p0 ^ p1) we substitute it's
// inlying point with the crossing point.
// this is calculated by taking the distance from the point to radius
// then this ratio is used to traverse the line and find the subtitute point
int
	accurate_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	int		p0_check;
	int		p1_check;

	p0_check = horizon_pythagoras(fdf, line->p0);
	p1_check = horizon_pythagoras(fdf, line->p1);
	if (p0_check && p1_check)
		return (EXIT_FAILURE);
	if (!p0_check && !p1_check)
		return (EXIT_SUCCESS);
	if (p0_check)
	{
		while (distance_pythagoras(line->p0->x + line->i,
			line->p0->y + line->j) < fdf->radius
			&& line->i != line->d_ctl)
			{
				while (line->err >= 0)
				{
					line->j += 1;
					line->err -= line->d_ctl;
				}
				line->i += 1;
				line->err += line->d_pas;
			}
		// printf("p0(%f,%f)\tSUB(%f,%f)\tp1(%f,%f)\n",
		// 	line->p0->x, line->p0->y,
		// 	line->p0->x + line->i, line->p0->y + line->j,
		// 	line->p1->x, line->p1->y);
	}
	return (EXIT_SUCCESS);
}

int
	darksquare(
		const t_fdf *fdf,
		const t_point *point)
{
	if (ft_abs(point->x) < fdf->darksquare * fdf->scale.total
		&& ft_abs(point->y) < fdf->darksquare * fdf->scale.total)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

// then we use pythagoras' theorum to see if x,y falls within the horizon
// cases:
// if both points are over the horizon; return (1)
// if both points are outside the horizon; return (0)
// if only one point is over the horizon;
//;malloc a new point (with colour) exactly on the horizon and return (0)
int
	over_the_horizon(
		const t_fdf *fdf,
		t_line *line)
{
	if (fdf->ballin == false)
		return (EXIT_SUCCESS);
	if ((line->p0->z < -0.00001 && line->p1->z < -0.00001))
	{
		if (darksquare(fdf, line->p0) && darksquare(fdf, line->p1))
			return (EXIT_FAILURE);
		if (accurate_horizon(fdf, line) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
